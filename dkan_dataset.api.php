<?php

/**
 * @file
 * Hooks provided by DKAN Dataset module.
 */

/**
 * @addtogroup hooks
 * @{
 */


/**
 * Add to or alter the array of external previews available to DKAN Dataset
 *
 * @param array $previews
 *   An associative array of preview types containing the elements "name" (the
 *   publicly-viewable name for this preview type), "link_callback" and"format".
 *   "link_callback" provides a function that will be called and passed the
 *   dataset node object to generate the actual link URL for the preview. See
 *   the default previdews defined in
 *   dkan_dataset_teaser_get_external_previews() for examples. After all alter
 *   hooks have run, the array will be parsed by
 *   dkan_dataset_teaser_get_external_previews() and a "url" element added.
 *   "Format" sets the default resource format that the preview will be enabled
 *   for; this can be overridden in the admin settings form at
 *   admin/dkan/dataset_preview.
 *
 * @param $node
 *   The dataset node object.
 */
function hook_dkan_dataset_external_previews_alter(&$previews, $node) {
  $previews['third_party_service'] = array(
    'name' => 'Third-Party Mapping Service',
    'link_callback' => 'mymodule_preview_link',
    'format' => array('geojson'),
  );
}

/**
 * @} End of "addtogroup hooks".
 */
