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
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 1,
    'access_author' => '',
    'i18n' => 0,
    'module' => 'kdb_feeds',
    'locked' => array(
      '0' => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;
}

/**
 * Implementation of hook_rules_defaults().
 */
function kdb_feeds_rules_defaults() {
  return array(
    'rules' => array(
      'rules_kkb_feeds_mobileapp_flagged' => array(
        '#type' => 'rule',
        '#set' => 'event_flag_flagged_kdb_feeds_mobileapp',
        '#label' => 'A node was flagged for display in the mobile app.',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'kkb_feeds',
          'kdb_feeds' => 'kdb_feeds',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#info' => array(
              'label' => 'Clear the cache of a specific view.',
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'View',
                  'description' => 'Specify the view you want to clear.',
                ),
              ),
              'module' => 'Cache Actions',
            ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#settings' => array(
              'view' => 'kdb_feeds_mobileapp',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'view' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#type' => 'action',
          ),
        ),
        '#version' => 6003,
      ),
      'rules_kkb_feeds_mobileapp_unflagged' => array(
        '#type' => 'rule',
        '#set' => 'event_flag_unflagged_kdb_feeds_mobileapp',
        '#label' => 'A node was unflagged from display in the mobile app.',
        '#active' => 1,
        '#weight' => '0',
        '#categories' => array(
          '0' => 'kkb_feeds',
          'kdb_feeds' => 'kdb_feeds',
        ),
        '#status' => 'default',
        '#conditions' => array(),
        '#actions' => array(
          '0' => array(
            '#weight' => 0,
            '#type' => 'action',
            '#settings' => array(
              'view' => 'kdb_feeds_mobileapp',
              '#eval input' => array(
                'token_rules_input_evaluator' => array(
                  'view' => array(
                    '0' => ':global',
                  ),
                ),
              ),
            ),
            '#name' => 'cache_actions_action_clear_views_cache',
            '#info' => array(
              'label' => 'Clear the cache of a specific view.',
              'arguments' => array(
                'view' => array(
                  'type' => 'string',
                  'label' => 'View',
                  'description' => 'Specify the view you want to clear.',
                ),
              ),
              'module' => 'Cache Actions',
            ),
          ),
        ),
        '#version' => 6003,
      ),
    ),
  );
}

/**
 * Implementation of hook_views_api().
 */
function kdb_feeds_views_api() {
  return array(
    'api' => '2',
  );
}
