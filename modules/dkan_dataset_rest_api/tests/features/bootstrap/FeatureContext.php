<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\Step\Given;
use Symfony\Component\Process\Process;

require 'vendor/autoload.php';
include_once 'dkan_dataset_rest_api_crud.php';

class FeatureContext extends DrupalContext {

  private $dataset_nid;

  /**
   * @Given /^I use the Dataset REST API to create:$/
   */
  public function iUseTheDatasetRestApiToCreate($data) {
    $base_url = $this->getMinkParameter('base_url');
    $endpoint = '/api/dataset';
    $entity = 'node';
    $login_url = $base_url . $endpoint . '/user/login';

    // Get cookie_session and csrf_token.
    $user_login = dkan_dataset_services_user_login($login_url);
    $cookie_session = $user_login['cookie_session'];
    $csrf_token = dkan_dataset_services_get_csrf($cookie_session, $user_login['curl'], $base_url);

    foreach ($data->getHash() as $node_data) {
      // Node data.
      $node_data = array(
        'title' => $node_data['title'],
        'type' => 'dataset',
        'body[und][0][value]' => $node_data['body'],
        'status' => $node_data['status'],
      );

      // Create node.
      $node = dkan_dataset_services_create_node($node_data, $csrf_token, $cookie_session, $base_url, $endpoint, $entity);
      $this->dataset_nid = $node->nid;
    }

    return true;
  }

  /**
   * @Given /^I use the Dataset REST API to update "test dataset":$/
   */
  public function iUseTheDatasetRestApiToUpdateTestDataset($data) {
    $base_url = $this->getMinkParameter('base_url');
    $endpoint = '/api/dataset';
    $entity = 'node';
    $login_url = $base_url . $endpoint . '/user/login';

    // Get cookie_session and csrf_token.
    $user_login = dkan_dataset_services_user_login($login_url);
    $cookie_session = $user_login['cookie_session'];
    $csrf_token = dkan_dataset_services_get_csrf($cookie_session, $user_login['curl'], $base_url);

    foreach ($data->getHash() as $node_data) {
      // Node data.
      $node_data = array(
        'title' => 'Dataset updated',
        'body[und][0][value]' => $node_data['body'],
      );

      // Update node.
      $response = dkan_dataset_services_update_node($node_data, $this->dataset_nid, $csrf_token, $cookie_session, $base_url, $endpoint, $entity);
    }

    return true;
  }

  /**
   * @Given /^I use the Dataset REST API to delete "Dataset updated":$/
   */
  public function iUseTheDatasetRestApiToDeleteDatasetUpdated() {
    $base_url = $this->getMinkParameter('base_url');
    $endpoint = '/api/dataset';
    $entity = 'node';
    $login_url = $base_url . $endpoint . '/user/login';

    // Get cookie_session and csrf_token.
    $user_login = dkan_dataset_services_user_login($login_url);
    $cookie_session = $user_login['cookie_session'];
    $csrf_token = dkan_dataset_services_get_csrf($cookie_session, $user_login['curl'], $base_url);


   //Delete node.
   $response = dkan_dataset_services_delete_node($this->dataset_nid, $csrf_token, $cookie_session, $base_url, $endpoint, $entity);

    return true;
  }


}
