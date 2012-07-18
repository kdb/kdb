<?php
/**
 * @file
 * Import event feeds.
 */


/**
 * Base class for all our migrations.
 */
abstract class KDBFeedImportBase extends XMLMigration {
  /**
   * Basic migration configuration.
   */
  public function __construct() {
    parent::__construct();

    // The who's who for this migration.
    $this->team = array(
      new MigrateTeamMember('Mikkel Høgh', 'mikkel@revealit.dk', t('Implementor')),
    );

    // The path to the migration files.
    $this->migration_files_path = file_directory_path() . '/smsq_migrate/';
  }

  /**
   * Provide a toString method for Migrate.
   */
  public function __toString() {
    return get_class($this);
  }
}

/**
 * KDBEventFeedSource.
 */
class KDBFeedImportSource extends MigrateSource {
  protected $position = 0;
  protected $entries = array();

  /**
   * The URL of the feed we're importing.
   *
   * @var string
   */
  protected $feedURL;

  /**
   * Instantiate the MigrateSource by loading and parsing the feed.
   */
  public function __construct($feed_url) {
    $this->feedURL = $feed_url;
    $this->institutionMap = variable_get('kdb_feed_import_instiution_map', array());

    // Fetch the feed XML.
    $request = drupal_http_request($this->feedURL);

    // Convert to DOM document.
    $feed = new DOMDocument();
    $feed->loadXML($request->data);

    $institutions = array();

    foreach ($feed->getElementsByTagName('entry') as $element) {
      $entry = (object) array(
        'id' => self::getXMLNodeValue($element, 'id'),
        'title' => self::getXMLNodeValue($element, 'title'),
        'published' => self::getXMLNodeValue($element, 'published'),
        'updated' => self::getXMLNodeValue($element, 'updated'),
        'author' => self::getXMLNodeValue($element, 'author'),
        'summary' => self::getXMLNodeValue($element, 'summary'),
        'content' => self::getXMLNodeValue($element, 'content'),
        'startdate' => self::getXMLNodeValue($element, 'startdate'),
        'enddate' => self::getXMLNodeValue($element, 'enddate'),
        'price' => self::getXMLNodeValue($element, 'price'),
        'images' => array(),
      );

      foreach ($element->getElementsByTagName('image') as $img) {
        $entry->images[] = $img->nodeValue;
      }

      $institution = $element->getElementsByTagName('institution')->item(0)->getAttribute('id');

      // Map the foreign site's institution ID to a local node ID.
      if (!empty($this->institutionMap[$institution])) {
        $entry->institution = $this->institutionMap[$institution];

        // Only import events that references an existing institution.
        $this->entries[] = $entry;
      }
    }
  }

  /**
   * Provide a toString method for Migrate.
   */
  public function __toString() {
    return get_class($this);
  }

  /**
   * Return the list of fields this source provides.
   */
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
      'images',
    );
  }

  /**
   * Restart the migration.
   */
  public function performRewind() {
    $this->position = 0;
  }

  /**
   * Return number of entries.
   */
  public function computeCount() {
    return count($this->entries);
  }

  /**
   * Get the next entry to be migrated.
   */
  public function getNextRow() {
    $position = $this->position;

    if (isset($this->entries[$position])) {
      // Increment the position, so the next call will return the next entry.
      $this->position++;

      return $this->entries[$position];
    }
  }

  /**
   * Get text content of named XML element.
   *
   * @param DOMNode $node
   *   The DOM node (full document, element, etc.) to work on.
   * @param string $name
   *   Name of the field to get.
   *
   * @return string
   *   Content of the specified element, empty string if not found.
   */
  public static function getXMLNodeValue(DOMNode $node, $name) {
    $elem = $node->getElementsByTagName($name)->item(0);

    if ($elem) {
      return $elem->nodeValue;
    }

    return '';
  }
}

/**
 * Base class for article migrations.
 */
class KDBEventFeedImport extends KDBFeedImportBase {
  /**
   * Configure the migration.
   */
  public function __construct() {
    parent::__construct();

    $this->description = 'Migrate events from event feeds.';

    // The source ID here is the one retrieved from the XML feed, and is
    // used to identify the specific item's file.
    $this->map = new MigrateSQLMap($this->getMachineName(),
      array(
        'id' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationNode::getKeySchema()
    );

    // URL for event feed. The items and list is the same feed.
    $this->list_url = variable_get('kdb_feed_import_event_url', FALSE);
    $this->item_url = $this->list_url;

    // Migrate from the feed.
    $this->source = new KDBFeedImportSource($this->list_url);

    // Migrate to event nodes.
    $this->destination = new MigrateDestinationNode('event');

    // Maps the source fields to node values.
    $this->addFieldMapping('title', 'title');
    $this->addFieldMapping('body', 'content');
    $this->addFieldMapping('created', 'published');
    $this->addFieldMapping('changed', 'updated');
    $this->addFieldMapping('field_teaser', 'summary');
    $this->addFieldMapping('name', 'author');
    $this->addFieldMapping('field_library_ref', 'institution');

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
    $node->title = html_entity_decode($node->title, ENT_COMPAT | ENT_XML1, 'UTF-8');
    $node->body = html_entity_decode($node->body, ENT_COMPAT | ENT_XML1, 'UTF-8');

    // Start and end time are in the same field.
    $node->field_datetime[0]['value'] = self::convertTimestamp($row->startdate);
    $node->field_datetime[0]['value2'] = self::convertTimestamp($row->enddate);

    // Save files.
    $node->field_list_image = array();
    foreach ($row->images as $image_url) {
      $node->field_list_image[] = self::saveFileFromURL($image_url);
    }

    if (!empty($row->price)) {
      $matches = array();

      // field_entry_price is supposed to be a number, so we sanitise it.
      if (preg_match('/(\d\d+(?:,\d\d)?)/', str_replace('.', '', $row->price), $matches) && !empty($matches[1])) {
        $node->field_entry_price[0]['value'] = str_replace(',', '.', $matches[1]);

        // Add the price info to the body text.
        $node->body = $node->body . "\n\n\n\n<p><strong>Pris:</strong> " . $price . '</p>';
      }
    }
  }

  /**
   * Save imported file to disk.
   */
  public static function saveFileFromURL($url) {
    $ch = curl_init(urldecode($url));

    // Create a temporary file for the download.
    $tempfile = tempnam(file_directory_temp(), 'kdb_feed_import');
    $fp = fopen($tempfile, "w");

    // Write the downloaded data to the temporary file.
    curl_setopt($ch, CURLOPT_FILE, $fp);

    // Follow redirects.
    curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);

    // Don't include headers in output.
    curl_setopt($ch, CURLOPT_HEADER, FALSE);

    curl_exec($ch);
    curl_close($ch);
    fclose($fp);

    // Get the original filename from the URL.
    $url_parts = explode('/', parse_url($url, PHP_URL_PATH));
    $filename = urldecode(array_pop($url_parts));

    // Use transliteration module to sanitize the filename if possible.
    if (function_exists('transliteration_clean_filename')) {
      $filename = transliteration_clean_filename($filename);
    }

    // Make sure we have a suitable folder for saving the images.
    $imagepath = file_create_path('kdb_feed_import');
    $destination = $imagepath . '/' . $filename;

    if (file_check_directory($imagepath, FILE_CREATE_DIRECTORY)) {
      if (file_move($tempfile, $destination, FILE_EXISTS_REPLACE)) {
        $file = array(
          'filename' => $filename,
          'filepath' => $destination,
          'filemime' => file_get_mimetype($destination),
          'filesize' => filesize($destination),
          'destination' => $destination,
          'status' => FILE_STATUS_PERMANENT,
        );

        // If file already exists, load its curent data and store it,
        // before saving.
        $query = db_query("SELECT * FROM {files} WHERE filepath = '%s'", array(
          ':filepath' => $destination,
        ));
        if ($row = db_fetch_array($query)) {
          $file = array_merge($row, $file);
          drupal_write_record('files', $file, array('fid'));
        }
        // If not, create a new file entry.
        else {
          $file['timestamp'] = $_SERVER['REQUEST_TIME'];
          drupal_write_record('files', $file);
        }

        return $file;
      }
    }
  }
}
