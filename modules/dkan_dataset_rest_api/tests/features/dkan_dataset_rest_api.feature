Feature: DKAN Dataset REST API

  Scenario: Creating a Dataset
    Given I am on "/dataset"
      Then I should not see "test dataset"
    Given datasets:
      | title        | body       | status |
      | test dataset | body text  | 1      |
      When I am on "/dataset"
      Then I should see "test dataset"
