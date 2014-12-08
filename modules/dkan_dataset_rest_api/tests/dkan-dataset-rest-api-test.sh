#!/bin/bash

# Install dependencies
composer install

# Create Database
mysql -e 'drop database dkan_dataset_rest_test; create database dkan_dataset_rest_test;'

# Install DKAN
cd /tmp
drush -y dl drupal
cd -
mv /tmp/drupal-7.34 drupal
cd drupal
drush si --db-url=mysql://root:@127.0.0.1/dkan_dataset_rest_test --account-name=admin --account-pass=admin  --yes
drush cc all --yes
cp ../../../../dkan_dataset.make .
drush make dkan_dataset.make --yes --no-core
drush dl -y services
drush en -y dkan_dataset dkan_dataset_content_types dkan_dataset_rest_api

# Run test server
drush --root=$PWD runserver 8888 &
sleep 4
cd ../

bin/behat
rm dkan_dataset.make
