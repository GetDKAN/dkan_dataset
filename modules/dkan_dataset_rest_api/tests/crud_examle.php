<?php

/**
 * @file
 * Shows example of CRUD for server testing.
 */

include 'dkan_dataset_rest_api_crud.php';

// Set parameters.
$base_url = 'http://dataset-api.dkan.local';
$endpoint = '/api/dataset';
$entity = 'node';

$request_url = $base_url . $endpoint . '/user/login';
$user_login = dkan_dataset_services_user_login($request_url);
$cookie_session = $user_login['cookie_session'];
$csrf_token = dkan_dataset_services_get_csrf($cookie_session, $user_login['curl'], $base_url);

// Node data.
$node_data = array(
  'title' => 'A node created with services 3.x and REST server',
  'type' => 'page',
  'body[und][0][value]' => '<p>Body</p>',
);
// Create node.
$node = dkan_dataset_services_create_node($node_data, $csrf_token, $cookie_session, $base_url, $endpoint, $entity);
var_dump($node);
// Updated node data.
$node_data = array(
  'title' => 'A node UPDATED with services 3.x and REST server',
  'body[und][0][value]' => '<p>Body updated</p>',
);
// Update node.
$response = dkan_dataset_services_update_node($node_data, $node->nid, $csrf_token, $cookie_session, $base_url, $endpoint, $entity);
print_r($response);
// Delete node.
$response = dkan_dataset_services_delete_node($node->nid, $csrf_token, $cookie_session, $base_url, $endpoint, $entity);
print_r($response);
