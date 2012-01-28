# BigBlueButton for Drupal 7

## Source Code // Project Pages:
* BigBlueButton: http://code.google.com/p/bigbluebutton
* BigBlueButton for Drupal: http://drupal.org/project/bbb

## Installation and Setup:
1. Install a Working BigBlueButton Server: http://code.google.com/p/bigbluebutton/wiki/08InstallationUbuntu
2. Generate a Salt Code on BigBlueButton Server side with the following command: $ bbb-conf --salt
3. Download current dev version of BBB module and apply the following patch: http://drupal.org/files/issues/bbb-d7-1016910-21.patch (note use this command: $ patch -p1 < bbb-d7-1016910-21.patch) OR download from github.com: https://github.com/markwk/bbb/zipball/7.x-1.x
4. Enable BBB module
5. Configure BBB Settings at: admin/config/media/bigbluebutton by adding Base URL and Security Salt (Note: It's important there is no trailing / on the URL!)
6. Create a new type or edit an existing node type to "treate this node type as a meeting"