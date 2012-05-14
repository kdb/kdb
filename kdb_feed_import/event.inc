<?php
/**
 * @file
 * Import event feeds.
 */

/**
 * Base class for all our migrations.
 */
abstract class KDBFeedImportBase extends XMLMigration {
  public function __construct() {
    parent::__construct();

    // The who's who for this migration.
    $this->team = array(
      new MigrateTeamMember('Mikkel Høgh', 'mikkel@revealit.dk', t('Implementor')),
    );

    // The path to the migration files.
    $this->migration_files_path = file_directory_path() . '/smsq_migrate/';
  }
}

/**
 * KDBEventFeedSource.
 */
class KDBFeedImportSource extends MigrateSource{
  protected $position = 0;
  protected $entries = array();

  /**
   * The URL of the feed we're importing.
   *
   * @var string
   */
  protected $feedURL;

  public function __construct($feed_url) {
    $this->feedURL = $feed_url;

    // Fetch the feed XML.
    $request = drupal_http_request($this->feedURL);

    // Convert to DOM document 
    $feed = new DOMDocument();
    $feed->loadXML($request->data);

    $institutions = array();

    foreach ($feed->getElementsByTagName('entry') as $element) {
      $entry = (object) array(
        'id' => $element->getElementsByTagName('id')->item(0)->nodeValue,
        'title' => $element->getElementsByTagName('title')->item(0)->nodeValue,
        'published' => $element->getElementsByTagName('published')->item(0)->nodeValue,
        'updated' => $element->getElementsByTagName('updated')->item(0)->nodeValue,
        'author' => $element->getElementsByTagName('author')->item(0)->nodeValue,
        'summary' => $element->getElementsByTagName('summary')->item(0)->nodeValue,
        'content' => $element->getElementsByTagName('content')->item(0)->nodeValue,
        'startdate' => $element->getElementsByTagName('startdate')->item(0)->nodeValue,
        'enddate' => $element->getElementsByTagName('enddate')->item(0)->nodeValue,
        'price' => $element->getElementsByTagName('price')->item(0)->nodeValue,
        'institution' => $element->getElementsByTagName('institution')->item(0)->getAttribute('id'),
      );

      $this->entries[] = $entry;
    }
  }

  public function fields() {
    return array(
      'id',
      'title',
      'published',
      'updated',
      'author',
      'summary',
      'content',
      'startdate',
      'enddate',
      'ticketlink',
      'address',
      'email',
      'phone',
      'price',
    );
  }

  public function performRewind() {
    $this->position = 0;
  }

  public function computeCount() {
    return count($this->entries);
  }

  public function getNextRow() {
    $position = $this->position;

    if (isset($this->entries[$position])) {
      // Increment the position, so the next call will return the next entry.
      $this->position++;

      return $this->entries[$position];
    }
  }
}

/**
 * Base class for article migrations.
 */
class KDBEventFeedImport extends KDBFeedImportBase {
  public function __construct() {
    parent::__construct();

    $this->description = 'Migrate events from event feeds.';

    // The source ID here is the one retrieved from the XML feed, and is
    // used to identify the specific item's file
    $this->map = new MigrateSQLMap($this->getMachineName(),
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        )
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // URL for event feed.
    $this->list_url = variable_get('kdb_feed_import_event_url', FALSE);
    $this->item_url = $this->list_url;

    // Migrate to event nodes.
    $this->destination = new MigrateDestinationNode('event');

    $this->source = new KDBFeedImportSource(variable_get('kdb_feed_import_event_url', FALSE));
    $this->institutionMap = variable_get('kdb_feed_import_instiution_map', array());

    // Maps the source fields to node values.
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('created', 'published');
    $this->addFieldMapping('changed', 'updated');
    $this->addFieldMapping('field_entry_price', 'price');
    $this->addFieldMapping('field_teaser', 'summary');
    $this->addFieldMapping('name', 'author');

    // These fields do not appear in the field, so just assign a default value.
    // Use bibliotek.kk.dks default text format for editors.
    $this->addFieldMapping('format')->defaultValue(3);
    // We assume content is in Danish.
    $this->addFieldMapping('language')->defaultValue('da');
    // Create the node as published.
    $this->addFieldMapping('status')->defaultValue(1);
  }

  /**
   * Convert ISO8601 timestamp to a naive format so MySQL can understand it.
   */
  public static function convertTimestamp($timestamp) {
    // Nothing to do here.
    if (empty($timestamp)) {
      return;
    }

    $time = strtotime($timestamp);
    return date('Y-m-d H:i:s', $time);
  }

  /**
   * Alter each node before saving.
   *
   * Here we do the manual conversions not possible with addFieldMapping.
   */
  public function prepare(stdClass $node, stdClass $row) {
    // Decode HTML entities from title and body.
    $node->title = html_entity_decode($node->title);
    $node->body = html_entity_decode($node->body);

    // Start and end time are in the same field.
    $node->field_datetime[0]['value'] = self::convertTimestamp($row->startdate);
    $node->field_datetime[0]['value2'] = self::convertTimestamp($row->enadate);

    // Map the foreign site's institution ID to a local node ID.
    if (!empty($this->institutionMap[$row->institution])) {
      $node->field_library_ref[0]['nid'] = $this->institutionMap[$row->institution];
    }

    if (!empty($price)) {
      
      $matches = array();

      // field_entry_price is supposed to be a number, so we sanitise it.
      if (preg_match('/(\d\d+(?:,\d\d)?)/', str_replace('.', '', $price), $matches) && !empty($matches[1])) {
        $node->field_entry_price[0]['value'] = str_replace(',', '.', $matches[1]);

        // Add the price info to the body text.
        $node->body = $node->body . "\n\n\n\n<p><strong>Pris:</strong> " . $price . '</p>';
      }
      else {
        $node->field_entry_price[0]['value'] = 0;
      }
    }
  }
}
