## DKAN Dataset REST API

DKAN Dataset API uses the <a href="https://www.drupal.org/project/services">Services</a> module to create CRUD endpoint at ``api/dataset/node``. Any entity can have an endpoint such as users, groups, taxonomy terms. Entities can be enabled through the services module administrative interface at ``/admin/structure/services/list/dkan_dataset_api/resources``.

### Documentation
The <a href="https://www.drupal.org/project/services">Services module</a> has extensive documentation. Here are some entries of interest:

* <a href="https://www.drupal.org/node/783722">Testing Resources</a>
* <a href="https://www.drupal.org/node/1354202">Identifying field names</a>
* <a href="https://www.drupal.org/node/1827698">Using REST Server with 2-Legged OAuth Authentication (Example with Java Servlet)</a>
* <a href="http://tylerfrankenstein.com/code/drupal-services-csrf-token-firefox-poster">Services CSRF Token with FireFox Poster</a>

### Server Types
DKAN Dataset API comes with a REST Server. Other server types are also incldued but not turned on. Those include:

* OAUTH
* XML-RPC

### Repsonse Formats

* bencode
* json
* jsonp
* php
* xml
* yaml

### Request Parser Types
* application/json
* application/vnd.php.serialized
* application/x-www-form-urlencoded
* application/x-yaml
* application/xml
* multipart/form-data
* text/xml

### Authentication Modes

#### Session Authentication
Session authentication is enabled by default. With session authentication an inital request is made to the user login to requet a session cookie. That session cookie is then stored locally and sent with a request in the X-CSRF-Token header to authenticate the request.

#### Token Authentication
Token authenticaion can be enabled using the <a href="https://www.drupal.org/project/services_token_access">Services Token Access</a> module. This is less secure but is easier for community members to use.

#### Authentication Permissions
The permissions with which a user is granted depend on the user role. User roles and permissions are easily configured in the user administration screen at ``admin/people``.

### Creating a Dataset

Below is an example request to create a dataset

* request uri: http://example.com/api/dataset/node 
* request method: post
* content-type: application/json
* request body
```
{
    "type": "dataset",
    "title": "Wisconsin Polling Places",
    "og_group_ref": {
        "und": {
            // Node ids for two groups.
            "target_id": "2,3"
        }
    },
    "field_resources": {
        "und": [
            {
                // Resource title plus node id.
                "target_id": "Madison Polling Places (5)"
            }
        ]
    },
    "body": {
        "und": [
            {
                "value": "<p>Polling places in the state of Wisconsin.</p>"
            }
        ]
    },
    "field_author": {
        "und": [
            {
                "value": "Bob Lafollette"
            }
        ]
    },
    "field_contact_email": {
        "und": [
            {
                "value": "admin@example.com"
            }
        ]
    }
}
```
* response
```
{
    "nid": "131",
    "uri": "http://example.com/api/dataset/node/131"
}
```

### Services Stack Exchange

The Sessions module has a thriving community on Stack Exchange. Questions can be posted to DKAN community resources:

* http://gitub.com/nucvic/dkan/issues
* https://groups.google.com/forum/#!forum/dkan-dev

or to the Sessions tag on the Drupal Stack Exchange:

* http://drupal.stackexchange.com/questions/tagged/services

