<?php

/**
 * Implementation of hook_views_default_views().
 */
function kdb_feeds_views_default_views() {
  $views = array();

  // Exported view: kdb_feeds_article
  $view = new view;
  $view->name = 'kdb_feeds_article';
  $view->description = 'Using ding_event_feed to publish articles for use on other sites.';
  $view->tag = 'kdb_feeds';
  $view->base_table = 'node';
  $view->core = 6;
  $view->api_version = '2';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('sorts', array(
    'created' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'article' => 'article',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 100);
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'build_mode' => 'full',
    'links' => 1,
    'comments' => 0,
  ));
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'ding_atom');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'ding_event_feed_row_atom');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'item_length' => 'default',
    'ding_audience' => '',
    'ding_keywords' => '1',
    'ding_tags' => '2',
    'ding_teaser' => 'field_teaser',
    'ding_image' => 'field_list_image',
    'ding_date' => '',
    'ding_entry_price' => '',
    'ding_library' => 'field_library_ref',
  ));
  $handler->override_option('path', 'kdb_feeds/article.xml');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);

  $views[$view->name] = $view;

  // Exported view: kdb_feeds_event
  $view = new view;
  $view->name = 'kdb_feeds_event';
  $view->description = 'Using ding_event_feed to publish events for use on other sites.';
  $view->tag = 'kdb_feeds';
  $view->base_table = 'node';
  $view->core = 6;
  $view->api_version = '2';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'destid1' => array(
      'id' => 'destid1',
      'table' => 'migrate_map_kdbeventfeedimport',
      'field' => 'destid1',
    ),
  ));
  $handler->override_option('sorts', array(
    'created' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'created',
      'table' => 'node',
      'field' => 'created',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'event' => 'event',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'sourceid1' => array(
      'operator' => 'empty',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'sourceid1',
      'table' => 'migrate_map_kdbeventfeedimport',
      'field' => 'sourceid1',
      'relationship' => 'none',
    ),
    'date_filter_1' => array(
      'operator' => '>=',
      'value' => array(
        'min' => array(
          'date' => '',
        ),
        'max' => array(
          'date' => '',
        ),
        'value' => array(
          'date' => '',
        ),
        'default_date' => 'now',
        'default_to_date' => '',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'date_fields' => array(
        'node_data_field_datetime.field_datetime_value' => 'node_data_field_datetime.field_datetime_value',
      ),
      'date_method' => 'OR',
      'granularity' => 'day',
      'form_type' => 'date_text',
      'default_date' => 'now',
      'default_to_date' => '',
      'year_range' => '-3:+3',
      'id' => 'date_filter_1',
      'table' => 'node',
      'field' => 'date_filter',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 100);
  $handler->override_option('row_plugin', 'node');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'build_mode' => 'full',
    'links' => 1,
    'comments' => 0,
  ));
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'ding_atom');
  $handler->override_option('style_options', array(
    'mission_description' => FALSE,
    'description' => '',
  ));
  $handler->override_option('row_plugin', 'ding_event_feed_row_atom');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'item_length' => 'default',
    'ding_audience' => '5',
    'ding_keywords' => '4',
    'ding_tags' => '2',
    'ding_teaser' => 'field_teaser',
    'ding_image' => 'field_list_image',
    'ding_date' => 'field_datetime',
    'ding_entry_price' => 'field_entry_price',
    'ding_library' => 'field_library_ref',
  ));
  $handler->override_option('path', 'kdb_feeds/event.xml');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', FALSE);

  $views[$view->name] = $view;

  // Exported view: kdb_feeds_mobileapp
  $view = new view;
  $view->name = 'kdb_feeds_mobileapp';
  $view->description = 'Content feed for mobile app';
  $view->tag = 'kdb_feeds';
  $view->base_table = 'node';
  $view->core = 0;
  $view->api_version = '2';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('relationships', array(
    'flag_content_rel' => array(
      'label' => 'flag',
      'required' => 1,
      'flag' => 'kdb_feeds_mobileapp',
      'user_scope' => 'any',
      'id' => 'flag_content_rel',
      'table' => 'node',
      'field' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'timestamp' => array(
      'order' => 'DESC',
      'granularity' => 'second',
      'id' => 'timestamp',
      'table' => 'flag_content',
      'field' => 'timestamp',
      'relationship' => 'flag_content_rel',
      'override' => array(
        'button' => 'Override',
      ),
    ),
  ));
  $handler->override_option('filters', array(
    'status' => array(
      'operator' => '=',
      'value' => '1',
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'status',
      'table' => 'node',
      'field' => 'status',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'rules',
  ));
  $handler->override_option('title', 'Indhold til mobil-app');
  $handler->override_option('empty', 'Ingen nyheder udvalgt.');
  $handler->override_option('empty_format', '1');
  $handler->override_option('items_per_page', 20);
  $handler->override_option('row_plugin', 'node');
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->override_option('style_plugin', 'rss');
  $handler->override_option('style_options', array(
    'mission_description' => 0,
    'description' => 'Udvalgt indhold fra bibliotek.kk.dk',
  ));
  $handler->override_option('row_plugin', 'kdb_redia_rss');
  $handler->override_option('row_options', array(
    'relationship' => 'none',
    'item_length' => 'default',
  ));
  $handler->override_option('path', 'kdb_feeds/mobileapp.xml');
  $handler->override_option('menu', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));
  $handler->override_option('displays', array());
  $handler->override_option('sitename_title', 0);

  $views[$view->name] = $view;

  return $views;
}
