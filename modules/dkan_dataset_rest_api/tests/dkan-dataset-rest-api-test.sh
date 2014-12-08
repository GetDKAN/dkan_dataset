#!/bin/bash

# Install dependencies
composer install

# Create Database
mysql -e 'drop database dkan_dataset_rest_test; create database dkan_dataset_rest_test;'

# Install DKAN
cd ..
cp ../../../dkan_dataset.make .
drush make --prepare-install build-dkan.make --yes test/drupal
cd test/drupal
drush si --sites-subdir=default --db-url=mysql://root:@127.0.0.1/dkan_test --account-name=admin --account-pass=admin  --site-name="DKAN" install_configure_form.update_status_module='array(FALSE,FALSE)' --yes
drush cc all --yes
drush dl -y services
drush en -y dkan_dataset dkan_dataset_content_types dkan_dataset_rest_api

# Run test server
drush --root=$PWD runserver 8888 &
sleep 4
cd ../

bin/behat
