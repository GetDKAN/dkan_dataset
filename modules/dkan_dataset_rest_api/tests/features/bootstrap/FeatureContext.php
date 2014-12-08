<?php

use Drupal\DrupalExtension\Context\DrupalContext;
use Behat\Behat\Context\Step\Given;
use Symfony\Component\Process\Process;

require 'vendor/autoload.php';
include_once 'dkan_dataset_rest_api_crud.php';

class FeatureContext extends DrupalContext {

  /**
   * Creates Datasets with the REST API.
   * @Given /^datasets:$/
   */
  public function datasets(TableNode $table) {
    throw new PendingException();
  }
}
