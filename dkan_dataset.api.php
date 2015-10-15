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
 *   publicly-viewable name for this preview type), "pattern," "args" and 
 *   "format". "Pattern" is a string formatted for PHP's sprintf() funcion, and 
 *   args is the array of arguments to be passed in. See the default previdews
 *   defined in dkan_dataset_teaser_get_external_previews() for examples. After 
 *   all alter hooks have run, the array will be parsed by 
 *   dkan_dataset_teaser_get_external_previews() and a "url" element added.
 *
 * @param $node
 *   The dataset node object.
 */
function hook_dkan_dataset_external_previews_alter(&$previews, $node) {
  $previews['third_party_service'] = array(
    'name' => 'Third-Party Mapping Service',
    'pattern' => 'http://third-party-service.com/preview?url=%s',
    'args' => array(file_create_url($node->field_upload[LANGUAGE_NONE][0]['uri'])),
    'format' => array('geojson'),
  );	
}

/**
 * @} End of "addtogroup hooks".
 */
