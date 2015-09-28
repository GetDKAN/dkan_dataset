<?php

/**
 * @file
 * Theme functions for datasets.
 */

/**
 * Implements hook_theme().
 */
function dkan_dataset_theme() {
  $theme = array(
    'dkan_dataset_resource_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_release_date_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_modified_date_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_identifier_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_resource_teaser_view' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_teaser_link' => array(
      'variables' => array(
        'title' => NULL,
        'nid' => NULL,
        'desc' => NULL,
        'format' => NULL,
        'type' => NULL,
      ),
    ),
    'dkan_dataset_teaser_link_open_with' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_teaser_link_explore' => array(
      'variables' => array('node' => NULL),
    ),
    'dkan_dataset_teaser_link_original' => array(
      'variables' => array('node' => NULL),
    ),
  );
  return $theme;
}
/**
 * Outputs the identifier content.
 */
function theme_dkan_dataset_identifier_view($vars) {
  return '<div property="dcterms:identifier" class="field-name-field-identifier">' . $vars['node']->uuid . '</div>';
}

/**
 * Outputs the modified date content.
 */
function theme_dkan_dataset_modified_date_view($vars) {
  return '<div property="dcterms:modified" class="field-name-field-modified-date">' . date('Y-m-d', $vars['node']->changed) . '</div>';
}

/**
 * Outputs the release date content.
 */
function theme_dkan_dataset_release_date_view($vars) {
  return '<div property="dcterms:issued" class="field-name-field-release-date">' . date('Y-m-d', $vars['node']->created) . '</div>';
}

/**
 * Output the resource into the node content.
 */
function theme_dkan_dataset_resource_view($vars) {
  $output = '<h4>' . t('Data and Resources') . '</h4>';
  $node = entity_metadata_wrapper('node', $vars['node']);
  $nodes = $node->field_resources->value();
  $links = array();
  $output .= '<div property="dcat:distribution">';

  if (isset($nodes)) {
    $file_count = 0;
    foreach ($nodes as $node) {
      // Node could be empty if it has been deleted.
      if (!$node || !node_access('view', $node)) {
        continue;
      }
      $node_wrapper = entity_metadata_wrapper('node', $node);
      $body = $node_wrapper->body->value();
      $term = '';
      if (isset($body['safe_value'])) {
        $desc = '<p class="description">' . dkan_dataset_text_trim($body['safe_value'], 80) . '</p>';
      }
      else {
        $desc = '<p class="description"></p>';
      }
      $format = t("data");
      if (isset($node->field_format) && $node->field_format && $node_wrapper->field_format->value()) {
        $format = $node_wrapper->field_format->value()->name;
      }
      if (isset($node->field_upload[LANGUAGE_NONE])) {
        $type = 'file_upload';
        $file_count++;
      }
      elseif (isset($node->field_link_remote_file[LANGUAGE_NONE])) {
        $type = 'link_remote_file';
      }
      else {
        $type = 'link_api';
      }
      if (variable_get('dkan_dataset_teaser_preview', 'explore') == 'explore') {
        $link = theme('dkan_dataset_teaser_link_explore', array('node' => $node, 'type' => $type));
      }
      elseif (variable_get('dkan_dataset_teaser_preview', 'explore') == 'open_with') {
        $link = theme('dkan_dataset_teaser_link_open_with', array('node' => $node, 'format' => $format, 'type' => $type));
      }
      else {
        $link = theme('dkan_dataset_teaser_link_original', array('node' => $node, 'type' => $type));
      }
      $links[] = theme('dkan_dataset_teaser_link', array(
        'link' => $link, 'title' => $node->title, 'nid' => $node->nid, 'desc' => $desc,
        'format' => $format, 'type' => $type, 'node' => $node,
      ));
    }
    if ($file_count > 1) {
      $download_all = '<div property="dcat:Distribution"><span class="links">';
      $download_all .= l('Download All<i class="fa fa-download"><span> Download</span></i>', 'node/' . $vars['node']->nid . '/dataset/download', array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('btn', 'btn-primary')
        )
      ));
      $download_all .= '</span></div>';
      $links[] = $download_all;
    }
    $output .= theme('item_list', array('items' => $links, 'attributes' => array('class' => array('resource-list'))));
    // Close first dcat declaration.
    $output .= '</div>';
  }
  return $output;
}

/**
 * Provides direct link url for resource.
 */
function dkan_dataset_resource_direct_link($node) {
  if (isset($node->field_upload[LANGUAGE_NONE])) {
    $url = file_create_url($node->field_upload[LANGUAGE_NONE][0]['uri']);
  }
  elseif (isset($node->field_link_remote_file[LANGUAGE_NONE])) {
    $url = $node->field_link_remote_file[LANGUAGE_NONE][0]['uri'];
  }
  elseif (isset($node->field_link_api[LANGUAGE_NONE])) {
    $url = $node->field_link_api[LANGUAGE_NONE][0]['url'];
  }
  else {
    $url = '';
  }
  return $url;
}

/**
 * Provides "Open With" preview calling implementing modules. 
 */
function dkan_dataset_teaser_link_preview_open_with($format, $node) {
  $previews = array();
  drupal_alter('dkan_dataset_open_with', $previews);
  $links = array();
  foreach ($previews as $provider => $preview) {
    if (in_array($format, $preview['format'])) {
      $function = $preview['link_callback'];
      if (function_exists($function)) {
        $links[$provider] = array('url' => $function($node), 'name' => $preview['name']);
      }
    }
  }
  if ($links) {
    $open_with_text = t('Open With');
    $open_with =
    '<div class="btn-group">
      <button class="btn btn-primary" data-toggle="dropdown">' . $open_with_text . '</button>
        <button class="btn btn-primary" data-toggle="dropdown">
          <span class="caret"></span><span class="sr-only">Toggle dropdown</span>
        </button>
      <ul class="dropdown-menu">
    ';
    foreach ($links as $provider => $link) {
      $open_with .=
        '<li class="' . $provider . ' ">
          <a href="' . $link['url'] . '" title="">
            <span> ' . $link['name'] . '</span>
          </a>
        </li>';
    }
    $open_with .= '</ul></div>';
    return $open_with;
  }

}

/**
 * Implements hook_dkan_dataset_open_with().
 */
function dkan_dataset_dkan_dataset_open_with_alter(&$previews) {
  $previews['dkan'] = array(
    'name' => t('DKAN Preview'),
    'link_callback' => 'dkan_dataset_open_with_resource',
    'format' => array('csv'),
  );
}

/**
 * Callback for dkan preview.
 */
function dkan_dataset_open_with_resource($node) {
  return url('node/' . $node->nid);
}

/**
 * Theme function to create original version of teaser links on Datasets.
 */
function theme_dkan_dataset_teaser_link_original($vars) {
  $download_link = '';
  $explore_link = l(
    t('Explore Data'),
    'node/' . $vars['node']->nid,
    array(
      'attributes' => array(
        'class' => array('btn', 'btn-primary'),
      ),
    )
  );
  if ($vars['type'] == 'file_upload') {
    $download_link = l(
      '<i class="fa fa-download"><span> Download</span></i>',
      dkan_dataset_resource_direct_link($vars['node']),
      array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('btn', 'btn-primary', 'orig'),
        ),
      )
    );
  }
  $link = $explore_link . $download_link;
  return $link;
}

/**
 * Theme function to create "Explore" version of teaser links on Datasets.
 */
function theme_dkan_dataset_teaser_link_explore($vars) {
  $url = dkan_dataset_resource_direct_link($vars['node']);
  $resource_link = url('node/' . $vars['node']->nid);
  $link = '
  <div class="dropdown btn-group dkan-explore">
    <a href="#" class="btn btn-primary dropdown-toggle" data-toggle="dropdown">
      <i class="fa fa-share"></i>' .
        t('Explore') .
      '<span class="caret"></span>
    </a>
    <ul class="dropdown-menu">
  ';
  if ($vars['type'] == 'file_upload' || $vars['type'] == 'link_remote_file') {
    $link .=
    '<li><a href="' . $resource_link . '"><i class="fa fa-bar-chart"></i>' . t('Preview') . '</a></li>
     <li><a href="' .  $url . '" class="resource-url-analytics" target="_blank"><i class="fa fa-download"></i>' . t('Download') . '</a></li>';
  }
  else {
    $link .=
    '<li><a href="' . $resource_link . '"><i class="fa fa-info-circle"></i>' . t('More information') . '</a></li>
     <li><a href="' .  $url . '" target="_blank"><i class="fa fa-external-link"></i>' . t('Go to resource') . '</a></li>';
  }
  $link .= '</ul></div>';
  return $link;
}

/**
 * Theme function for DKAN Dataset teaser link.
 */
function theme_dkan_dataset_teaser_link($vars) {

  $desc = $vars['desc'];
  $output = '<div property="dcat:Distribution">';
  $format = '<span data-toggle="tooltip" data-placement="top" data-original-title="' . $vars['format'] . '" class="format-label" property="dc:format" data-format="' . $vars['format'] . '">' . $vars['format'] . '</span>';

  $title = l($vars['title'] . $format, 'node/' . $vars['nid'], array(
    'html' => TRUE,
    'attributes' => array(
      'class' => array('heading'),
      'title' => $vars['title'],
      'property' => 'dcat:accessURL',
    ))
  );
  $output .= $title . $desc . '<span class="links">' .  $vars['link'] . '</span></div>';

  return $output;
}


/**
 * Theme function to create "open with" version of teaser links on Datasets.
 */
function theme_dkan_dataset_teaser_link_open_with($vars) {
  $url = dkan_dataset_resource_direct_link($vars['node']);
  if ($vars['type'] == 'file_upload' || $vars['type'] == 'link_remote_file') {
    $link = l(
      '<i class="fa fa-download"><span>' . t('Download') . '</span></i>',
      $url,
      array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('btn', 'btn-primary', 'data-link'),
        ),
      )
    );
  }
  else {
    $link = l(
      '<i class="fa fa-external-link"><span>' . t('Visit page') . '</span></i>',
      $url,
      array(
        'html' => TRUE,
        'attributes' => array(
          'class' => array('btn', 'btn-primary', 'data-link'),
        ),
      )
    );
  }

  $link = dkan_dataset_teaser_link_preview_open_with($vars['format'], $vars['node']) . $link;

  return $link;

}

/**
 * Output the resource into the node content.
 */
function theme_dkan_dataset_resource_teaser_view($vars) {
  if ($vars['node']->type == 'dataset') {
    $node = entity_metadata_wrapper('node', $vars['node']);
    $nodes = $node->field_resources->value();
  }
  else {
    $nodes = array($vars['node']);
  }
  $links = array();
  if (isset($nodes)) {
    // Data links for generate grouping resources link.
    $links_data = array();
    foreach ($nodes as $node) {
      $node_wrapper = entity_metadata_wrapper('node', $node);
      $name = dkan_dataset_get_resource_format($node);
      $term = '';

      //Check node is published.
      if ($node->status) {
        if (!isset($links_data[$name])) {
          $links_data[$name] = array(
            'term_name' => $name,
            'count' => 1,
            'url' => 'node/' . $vars['node']->nid,
            'link' => array(
              'attributes' => array(
                'class' => array('label'),
                'title' => t('Resources') . ': ' . $vars['node']->title,
                'data-format' => $name,
              ),
            ),
          );
        }
        else {
          $links_data[$name]['count'] = $links_data[$name]['count'] + 1;
        }
      }
    }
    foreach ($links_data as $term_name => $link) {
      $links[] = '<span class="count-resource">' . $link['count'] . 'x</span>' . l($term_name, $link['url'], $link['link']);
    }
    $output = theme('item_list', array('items' => $links, 'attributes' => array('class' => array('resource-list'))));
  }
  return $output;
}
