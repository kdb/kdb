; Additional modules, themes and libraries used on bibliotek.kk.dk.
; This is in addition to the modules provided by Ding.

api = 2
core = 6.x

; Our custom theme.
projects[copenhagen][type] = theme
projects[copenhagen][download][type] = git
projects[copenhagen][download][url] = https://github.com/kdb/copenhagen.git
projects[copenhagen][download][revision] = 89faaad

; Additional Ding-modules.
projects[ding_borger_api][type] = "module"
projects[ding_borger_api][download][type] = "git"
projects[ding_borger_api][download][url] = "https://github.com/dingproject/ding-borger-api.git"
projects[ding_borger_api][download][revision] = "v1.0.4"

projects[ding_eresource][type] = "module"
projects[ding_eresource][download][type] = "git"
projects[ding_eresource][download][url] = "https://github.com/kdb/ding-eresource.git"
projects[ding_eresource][download][revision] = 9db773a71e0e497d18064dba5c6b48715dbe9677

projects[ding_event_feeds][type] = module
projects[ding_event_feeds][download][type] = git
projects[ding_event_feeds][download][url] = https://github.com/kdb/ding-event-feeds.git
projects[ding_event_feeds][download][revision] = 6.x-1.1

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
projects[ding_tabroll][download][revision] = v1.0.2

projects[ding_wayf][type] = module
projects[ding_wayf][download][type] = git
projects[ding_wayf][download][url] = https://github.com/dingproject/ding_wayf.git
projects[ding_wayf][download][revision] = 4eaf964aa2294e66d312d9f47675787fbb3abc51

projects[ding_webtrends][type] = module
projects[ding_webtrends][download][type] = git
projects[ding_webtrends][download][url] = https://github.com/kdb/ding_webtrends.git
projects[ding_webtrends][download][revision] = v1.0.0-rc.2

projects[ding_wysiwyg_node_picker][type] = "module"
projects[ding_wysiwyg_node_picker][download][type] = "git"
projects[ding_wysiwyg_node_picker][download][url] = "https://github.com/dingproject/ding-wysiwyg-node-picker.git"
projects[ding_wysiwyg_node_picker][download][revision] = "v1.0.0"

projects[tinymce_node_picker][subdir] = "contrib"
projects[tinymce_node_picker][version] = "2.1"

; Additional contrib modules.
projects[autoload][subdir] = contrib
projects[autoload][version] = 2.1

projects[addthis][subdir] = contrib
projects[addthis][version] = 3.0-beta2

projects[backup_migrate][subdir] = contrib
projects[backup_migrate][version] = 2.5

projects[better_messages][subdir] = contrib
projects[better_messages][version] = 1.13

projects[dbtng][subdir] = contrib
projects[dbtng][version] = 1.0-rc4

projects[elysia_cron][subdir] = contrib
projects[elysia_cron][version] = 2.1

projects[flag][subdir] = contrib
projects[flag][version] = 2.0-beta6

projects[l10n_update][subdir] = contrib
projects[l10n_update][version] = 1.0-beta3

projects[memcache][subdir] = contrib
projects[memcache][version] = 1.10

projects[migrate][subdir] = contrib
projects[migrate][version] = 2.3

projects[module_filter][subdir] = contrib
projects[module_filter][version] = 1.7

projects[scheduler][subdir] = "contrib"
projects[scheduler][version] = "1.8"

; Mobile site

projects[alternator][type] = theme
projects[alternator][download][type] = git
projects[alternator][download][revision] = 67dc32e
projects[alternator][download][url] = https://github.com/kdb/alternator.git

projects[browscap][subdir] = contrib
projects[browscap][version] = 1.5

projects[cph-mobile][type] = theme
projects[cph-mobile][download][type] = git
projects[cph-mobile][download][url] = https://github.com/kdb/cph-mobile.git
projects[cph-mobile][download][revision] = 0e65df0

projects[ding-mobile][type] = module
projects[ding-mobile][download][type] = git
projects[ding-mobile][download][url] = https://github.com/kdb/ding-mobile.git
projects[ding-mobile][download][revision] = 9fbc4e3

projects[mobile_tools][subdir] = contrib
projects[mobile_tools][version] = 2.3

; Libraries

libraries[emogrifier][download][type] = get
libraries[emogrifier][download][url] = https://gist.github.com/gists/1344848/download
libraries[emogrifier][directory_name] = emogrifier
libraries[emogrifier][destination] = modules/ding_borger_api/ding_borger_api/lib
