[![Build Status](https://travis-ci.org/nuams/dkan_dataset.png?branch=7.x-1.x)](https://travis-ci.org/nuams/dkan_dataset)

# DKAN Dataset

This is a Drupal module containing the content types and other functionality to publish Open Data sets in Drupal.

DKAN Dataset is a standalone module that can be added to any existing Drupal 7 site.

DKAN Dataset is part of the [DKAN](https://drupal.org/project/dkan "DKAN homepage") project which includes the [DKAN profile](https://drupal.org/project/dkan "DKAN homepage") which creates a standalone Open Data portal, and [DKAN Datastore](https://drupal.org/project/dkan_datastore "DKAN Datastore homepage") which is a module that can be coupled with DKAN Dataset to offer a datastore and data previews.

DKAN Dataset is currently managed in code on Github but is mirrored on Drupal.org.

## INSTALLATION

This module REQUIRES implementers to use "drush make". If you only use "drush download" you will miss key dependencies for required modules and libraries.

The following will download the required libraries and patched modules:

```bash
drush dl dkan_dataset
cd dkan_dataset
drush make --no-core dkan_dataset.make
```

## Contributing

We are accepting issues in the dkan issue thread only -> https://github.com/nuams/dkan/issues -> Please label your issue as **"component: dkan_dataset"** after submitting so we can identify problems and feature requests faster.

If you can, please cross reference commits in this repo to the corresponding issue in the dkan issue thread. You can do that easily adding this text:

```
nuams/dkan#issue_id
``` 

to any commit message or comment replacing **issue_id** with the corresponding issue id.