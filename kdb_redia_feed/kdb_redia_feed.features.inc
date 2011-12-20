<?php

/**
 * Implementation of hook_views_api().
 */
function kdb_redia_feed_views_api() {
  return array(
    'api' => '2',
    'path' => drupal_get_path('module', 'kdb_redia_feed') . '/plugins',
  );
}
