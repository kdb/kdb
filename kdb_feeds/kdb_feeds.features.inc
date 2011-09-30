<?php

/**
 * Implementation of hook_flag_default_flags().
 */
function kdb_feeds_flag_default_flags() {
  $flags = array();
  // Exported flag: "Mobil-app indhold".
  $flags['kdb_feeds_mobileapp'] = array(
    'content_type' => 'node',
    'title' => 'Mobil-app indhold',
    'global' => '1',
    'types' => array(
      '0' => 'article',
      '1' => 'event',
    ),
    'flag_short' => 'Vis i mobil-app',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Fjern Fra mobil-app',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        '0' => 5,
        '1' => 6,
      ),
      'unflag' => array(
        '0' => 5,
        '1' => 6,
      ),
    ),
    'show_on_page' => 0,
    'show_on_teaser' => 0,
    'show_on_form' => 1,
    'access_author' => '',
    'i18n' => 0,
    'api_version' => 2,
    'module' => 'kdb_feeds',
    'locked' => array(
      '0' => 'name',
    ),
  );
  return $flags;
}

/**
 * Implementation of hook_views_api().
 */
function kdb_feeds_views_api() {
  return array(
    'api' => '2',
  );
}
