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

### Examples

Below you can find examples for the most common use cases. We are going to use Session Authentication for this examples.

#### How to Log In and get the Session Cookie

```
// Setup request URL.
$request_url = 'http://example.com/api/dataset/user/login';

// Prepare user data.
$user_data = array(
    'username' => 'theusername',
    'password' => 'theuserpassword',
);
$user_data = http_build_query($user_data);

// Setup request.
$curl = curl_init($request_url);
curl_setopt($curl, CURLOPT_HTTPHEADER, array('Accept: application/json')); // Accept JSON response.
curl_setopt($curl, CURLOPT_POST, 1); // Do a regular HTTP POST.
curl_setopt($curl, CURLOPT_POSTFIELDS, $user_data); // Set POST data.
curl_setopt($curl, CURLOPT_HEADER, FALSE);
curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);

// Execute request and get response.
$response = curl_exec($curl);

// Process response.
$logged_user = json_decode($response);

// Save cookie session to be used on future requests.
$cookie_session = $logged_user->session_name . '=' . $logged_user->sessid;
```

#### How to get the CSRF Token

```
// Setup request URL.
$request_url = 'http://example.com/services/session/token';

// Setup request.
$curl = curl_init($request_url);
curl_setopt($curl, CURLOPT_HTTPHEADER, array('Accept: application/json')); // Accept JSON response.
curl_setopt($curl, CURLOPT_POST, 1); // Do a regular HTTP POST.
curl_setopt($curl, CURLOPT_COOKIE, "$cookie_session"); // Send the cookie session that we got after login.
curl_setopt($curl, CURLOPT_HEADER, FALSE);
curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);

// Execute request and save CSRF Token.
$csrf_token = curl_exec($curl);
```

#### How to create a Resource

```
// Setup request URL.
$request_url = 'http://example.com/api/dataset/node';

// Setup resource data.
// A great explanation on how to target each node field can be found on the 'Identifying field names' article linked on the 'Documentation' section.
$resource_data = array(
    'type' => 'resource',
    'title' => 'Example resource',
    'status' => 1,
    'body[und][0][value]' => 'The description'
);
$resource_data = http_build_query($resource_data);

// Setup request.
$curl = curl_init($request_url); 
curl_setopt($curl, CURLOPT_HTTPHEADER, array('Accept: application/json', 'X-CSRF-Token: ' . $csrf_token)); 
curl_setopt($curl, CURLOPT_POST, 1); // Do a regular HTTP POST.
curl_setopt($curl, CURLOPT_POSTFIELDS, $resource_data); // Set POST data.
curl_setopt($curl, CURLOPT_COOKIE, "$cookie_session");
curl_setopt($curl, CURLOPT_HEADER, FALSE);
curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);

// Execute request and get response.
$response = curl_exec($curl);
```

#### How to attach a file to a resource

```
// Setup request URL.
$request_url = 'http://example.com/api/dataset/node/' . $resource_id . '/attach_file';

// Setup file data.
$file_data = array(
    'files[1]' => curl_file_create($file),
    'field_name' => 'field_upload',
    'attach' => 1
);

// Setup request.
$curl = curl_init($request_url); 
curl_setopt($curl, CURLOPT_HTTPHEADER, array('Content-Type: multipart/form-data','Accept: application/json', 'X-CSRF-Token: ' . $csrf_token));
curl_setopt($curl, CURLOPT_POST, 1); // Do a regular HTTP POST.
curl_setopt($curl, CURLOPT_POSTFIELDS, $file_data); // Set POST data.
curl_setopt($curl, CURLOPT_COOKIE, "$cookie_session");
curl_setopt($curl, CURLOPT_HEADER, FALSE);
curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);

// Execute request and get response.
$response = curl_exec($curl);
```

#### How to create a Dataset

```
// Setup request URL.
$request_url = 'http://example.com/api/dataset/node';

// Setup dataset data.
// A great explanation on how to target each node field can be found on the 'Identifying field names' article linked on the 'Documentation' section.
$dataset_data = array(
    'type' => 'dataset',
    'title' => 'Example dataset',
    'status' => 1,
    'body[und][0][value]' => 'The description',
    'field_resources[und][0][target_id]' => 'Madison Polling Places (5)' // Resource title plus node id
    'field_author[und][0][value]' => 'Bob Lafollette'
);
$dataset_data = http_build_query($dataset_data);

// Setup request.
$curl = curl_init($request_url); 
curl_setopt($curl, CURLOPT_HTTPHEADER, array('Accept: application/json', 'X-CSRF-Token: ' . $csrf_token)); 
curl_setopt($curl, CURLOPT_POST, 1); // Do a regular HTTP POST.
curl_setopt($curl, CURLOPT_POSTFIELDS, $dataset_data); // Set POST data.
curl_setopt($curl, CURLOPT_COOKIE, "$cookie_session");
curl_setopt($curl, CURLOPT_HEADER, FALSE);
curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
curl_setopt($curl, CURLOPT_FAILONERROR, TRUE);

// Execute request and get response.
$response = curl_exec($curl);
```

### Services Stack Exchange

The Sessions module has a thriving community on Stack Exchange. Questions can be posted to DKAN community resources:

* http://gitub.com/nucvic/dkan/issues
* https://groups.google.com/forum/#!forum/dkan-dev

or to the Sessions tag on the Drupal Stack Exchange:

* http://drupal.stackexchange.com/questions/tagged/services
