Feature: DKAN Dataset REST API

  Scenario: Creating a Dataset
    Given I am on "/dataset"
      Then I should not see "test dataset"
    Given I use the Dataset REST API to create:
      | title        | body       | status |
      | test dataset | body text  | 1      |
      When I am on "/dataset"
      Then I should see "test dataset"
    Given I use the Dataset REST API to update "test dataset":
      | title        | body       | status |
      | test dataset | body text  | 0      |
      When I am on "/dataset"
      Then I should not see "test dataset"
    Given I use the Dataset REST API to update "test dataset":
      | title                | body       | status |
      | test dataset updated | body text  | 1      |
      When I am on "/dataset"
      Then I should see "test dataset updated"      
    Given I use the Dataset REST API to delete "test dataset updated":
      When I am on "/dataset"
      Then I should not see "test dataset updated"
