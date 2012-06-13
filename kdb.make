; Additional modules, themes and libraries used on bibliotek.kk.dk.
; This is in addition to the modules provided by Ding.

api = 2
core = 6.x

; Our custom theme.
projects[copenhagen][type] = theme
projects[copenhagen][download][type] = git
projects[copenhagen][download][url] = https://github.com/kdb/copenhagen.git
projects[copenhagen][download][revision] = v2.3.0

; Additional Ding-modules.
projects[ding_borger_api][type] = "module"
projects[ding_borger_api][download][type] = "git"
projects[ding_borger_api][download][url] = "https://github.com/dingproject/ding-borger-api.git"
projects[ding_borger_api][download][revision] = "v1.0.4"

projects[ding_eresource][type] = "module"
projects[ding_eresource][download][type] = "git"
projects[ding_eresource][download][url] = "https://github.com/kdb/ding-eresource.git"
projects[ding_eresource][download][revision] = 6.x-1.1

projects[ding_event_feeds][type] = module
projects[ding_event_feeds][download][type] = git
projects[ding_event_feeds][download][url] = https://github.com/kdb/ding-event-feeds.git
projects[ding_event_feeds][download][revision] = 6.x-1.0

projects[ding_faq][type] = "module"
projects[ding_faq][download][type] = "git"
projects[ding_faq][download][url] = "https://github.com/kdb/ding-faq.git"
projects[ding_faq][download][revision] = "v1.0.0-beta.3"

projects[ding_library_hours][type] = "module"
projects[ding_library_hours][download][type] = "git"
projects[ding_library_hours][download][url] = "https://github.com/kdb/ding-library-hours.git"
projects[ding_library_hours][download][revision] = "v1.0.0"

projects[ding_tabroll][type] = "module"
projects[ding_tabroll][download][type] = "git"
projects[ding_tabroll][download][url] = "https://github.com/kdb/ding_tabroll.git"
projects[ding_tabroll][download][revision] = v1.0.1

projects[ding_wysiwyg_node_picker][type] = "module"
projects[ding_wysiwyg_node_picker][download][type] = "git"
projects[ding_wysiwyg_node_picker][download][url] = "https://github.com/dingproject/ding-wysiwyg-node-picker.git"
projects[ding_wysiwyg_node_picker][download][revision] = "v1.0.0"

projects[tinymce_node_picker][subdir] = "contrib"
projects[tinymce_node_picker][version] = "2.1"

; Additional contrib modules.
projects[autoload][subdir] = contrib
projects[autoload][version] = 2.1

projects[backup_migrate][subdir] = contrib
projects[backup_migrate][version] = 2.5

projects[better_messages][subdir] = contrib
projects[better_messages][version] = 1.13

projects[dbtng][subdir] = contrib
projects[dbtng][version] = 1.0-rc4

projects[l10n_update][subdir] = contrib
projects[l10n_update][version] = 1.0-beta3

projects[memcache][subdir] = contrib
projects[memcache][version] = 1.10

projects[migrate][subdir] = contrib
projects[migrate][version] = 2.3

projects[scheduler][subdir] = "contrib"
projects[scheduler][version] = "1.8"

; Mobile site

projects[ding-mobile][type] = module
projects[ding-mobile][download][type] = git
projects[ding-mobile][download][url] = https://github.com/kdb/ding-mobile.git
projects[ding-mobile][download][revision] = 9fbc4e3

projects[mobile_tools][subdir] = contrib
projects[mobile_tools][version] = 2.3

projects[browscap][subdir] = contrib
projects[browscap][version] = 1.5

projects[alternator][type] = theme
projects[alternator][download][type] = git
projects[alternator][download][revision] = 67dc32e
projects[alternator][download][url] = https://github.com/kdb/alternator.git

projects[cph-mobile][type] = theme
projects[cph-mobile][download][type] = git
projects[cph-mobile][download][url] = https://github.com/kdb/cph-mobile.git
projects[cph-mobile][download][revision] = 0e65df0
