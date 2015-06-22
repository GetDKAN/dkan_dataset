core = 7.x
api = 2

; Set the default subdirectory for projects.
defaults[projects][subdir] = contrib

; Leaflet Draw Widget specific
projects[leaflet_draw_widget][download][type] = git
projects[leaflet_draw_widget][download][url] = "https://github.com/NuCivic/leaflet_draw_widget.git"
projects[leaflet_draw_widget][type] = module

includes[leaflet_draw_widget_make] = https://raw.githubusercontent.com/NuCivic/leaflet_draw_widget/967c8bb3eb13f3b70f28a4b487074b23591f1075/leaflet_widget.make

; Recline specific
projects[recline][download][type] = git
projects[recline][download][url] = https://github.com/NuCivic/recline.git
projects[recline][download][branch] = 7.x-1.x

includes[recline_make] = https://raw.githubusercontent.com/NuCivic/recline/431ffeaf4e22845fc83d1b4361a4e1d756e055ef/recline.make

; Contrib Modules
projects[beautytips][download][type] = git
projects[beautytips][download][branch] = 7.x-2.x
projects[beautytips][download][url] = "http://git.drupal.org/project/beautytips.git"
projects[beautytips][download][revision] = "472248d"
projects[beautytips][patch][849232] = http://drupal.org/files/include-excanvas-via-libraries-api-d7-849232-13.patch
projects[beautytips][type] = module

projects[entity][download][version] = 1.6
projects[entity][patch][2341611] = https://www.drupal.org/files/issues/entity-multivalue-token-replacement-fix-2341611-0.patch

projects[entity_rdf][download][type] = git
projects[entity_rdf][download][url] = http://git.drupal.org/project/entity_rdf.git
projects[entity_rdf][download][revision] = 7d91983
projects[entity_rdf][type] = module

projects[field_group][version] = 1.3
projects[field_group][patch][2042681] = http://drupal.org/files/issues/field-group-show-ajax-2042681-8.patch

projects[field_group_table][download][type] = git
projects[field_group_table][download][url] = "https://github.com/nuams/field_group_table.git"
projects[field_group_table][type] = module

projects[gravatar][download][type] = git
projects[gravatar][download][url] = "http://git.drupal.org/project/gravatar.git"
projects[gravatar][download][revision] = e933db3
projects[gravatar][patch][1568162] = http://drupal.org/files/views-display-user-picture-doesn-t-display-gravatar-1568162-10.patch
projects[gravatar][type] = module

projects[imagecache_actions][download][type] = git
projects[imagecache_actions][download][url] = "http://git.drupal.org/project/imagecache_actions.git"
projects[imagecache_actions][download][branch] = 7.x-1.x
projects[imagecache_actions][download][revision] = cd19d2a
projects[imagecache_actions][type] = module

projects[link_iframe_formatter][download][type] = git
projects[link_iframe_formatter][download][url] = "http://git.drupal.org/project/link_iframe_formatter.git"
projects[link_iframe_formatter][download][revision] = 228f9f4
projects[link_iframe_formatter][patch][2287233] = https://www.drupal.org/files/issues/link_iframe_formatter-coding-standards.patch
projects[link_iframe_formatter][type] = module

projects[multistep][download][type] = git
projects[multistep][download][url] = "http://git.drupal.org/project/multistep.git"
projects[multistep][download][revision] = 3b0d40a
projects[multistep][type] = module

projects[og][version] = 2.7
projects[og][patch][1090438] = http://drupal.org/files/issues/og-add_users_and_entities_with_drush-1090438-12.patch

projects[og_extras][download][type] = git
projects[og_extras][download][url] = "http://git.drupal.org/project/og_extras.git"
projects[og_extras][download][revision] = "b7e3587"
projects[og_extras][type] = module

projects[open_data_schema_map][type] = module
projects[open_data_schema_map][download][type] = git
projects[open_data_schema_map][download][url] = https://github.com/NuCivic/open_data_schema_map.git
projects[open_data_schema_map][download][branch] = master

projects[open_data_schema_map_dkan][type] = module
projects[open_data_schema_map_dkan][download][type] = git
projects[open_data_schema_map_dkan][download][url] = https://github.com/NuCivic/open_data_schema_map_dkan.git
projects[open_data_schema_map_dkan][download][branch] = master

projects[rdfx][download][type] = git
projects[rdfx][download][url] = http://git.drupal.org/project/rdfx.git
projects[rdfx][download][branch] = 7.x-2.x
projects[rdfx][download][revision] = cc7d4fc
projects[rdfx][patch][1271498] = http://drupal.org/files/issues/1271498_3_rdfui_form_values.patch

projects[ref_field][download][type] = git
projects[ref_field][download][url] = "http://git.drupal.org/project/ref_field.git"
projects[ref_field][patch][1670356] = http://drupal.org/files/removed_notice-1670356-1.patch
projects[ref_field][patch][2360019] = https://www.drupal.org/files/issues/ref_field-delete-insert-warning-2360019-0.patch
projects[ref_field][download][revision] = 9dbf7cf
projects[ref_field][type] = module

projects[remote_file_source][version] = 1.x
projects[remote_file_source][patch][2362487] = https://www.drupal.org/files/issues/remote_file_source-location-content-dist.patch

projects[uuid][version] = 1.0-alpha5
projects[uuid][patch][1927474] = http://drupal.org/files/unknown-column-in-field-list-fix-1927474-2.patch

; Libraries

libraries[chosen][type] = libraries
libraries[chosen][download][type] = git
libraries[chosen][download][url] = "https://github.com/harvesthq/chosen.git"
libraries[chosen][directory_name] = chosen
libraries[chosen][download][revision] = "a0ca7da1ae52235b5abb6f66d9218a20450116c1"

libraries[slugify][type] = libraries
libraries[slugify][download][type] = git
libraries[slugify][download][url] = "https://github.com/pmcelhaney/jQuery-Slugify-Plugin.git"
libraries[slugify][directory_name] = slugify
libraries[slugify][download][revision] = "79133a1bdfd3ac80d500d661a722b85c03a01da3"

libraries[arc][type] = libraries
libraries[arc][download][type] = git
libraries[arc][download][url] = "https://github.com/semsol/arc2.git"
libraries[arc][download][revision] = "44c396ab54178086c09499a1704e31a977b836d2"
libraries[arc][subdir] = "ARC2"

libraries[excanvas][download][type] = "file"
libraries[excanvas][download][url] = "https://explorercanvas.googlecode.com/files/excanvas_r3.zip"
libraries[excanvas][download][sha1] = "f1b9f7a44428eb0c7b27fe8ac0242d34ec94a385"
