<?php
// $Id$

/**
 * @file
 * Big Blue Button - Enables universities and colleges to deliver a high-quality
 * learning experience.
 *
 * @author
 * Stefan Auditor <stefan.auditor@erdfisch.de>
 */

/**
 * Administrative settings; Menu callback
 * TODO: Per node type settings?
 */
function bbb_settings() {
  if ($_POST['op'] == t('Test Connection')) {
    //TODO: Use batch api to test the whole set of bbb api functions
    bbb_test_connection($_POST['bbb_base_url'], $_POST['bbb_security_salt']);
  }

  $form = array();
  $form['bbb_drupal'] = array(
    '#title' => 'Meeting settings',
    '#type' => 'fieldset',
    '#description' => t('Goto !content_types_page to choose which node types should be treated as meetings it is possible to provide default settings there too. Also there are some Blocks available, that may be activated on the !block_page.', array('!content_types_page' => l('Content types administration page' , 'admin/content/types'), '!block_page' => l('Blocks administration page' , 'admin/build/block'))),
  );
  $form['bbb_server'] = array(
    '#title' => 'Server settings',
    '#type' => 'fieldset',
    '#description' => t('Adjust the default server settings. Read more about Big Blue Button on !home. See the documentation for !documentation. Goto !url to choose which node types should be treated as meetings.', array('!home' => l(t('BigBlueButton.org'), 'http://bigbluebutton.org/'), '!documentation' => l(t('installation instructions'), 'http://code.google.com/p/bigbluebutton/'), '!url' => l('Content types administration page' , 'admin/content/types'))),
  );
  $form['bbb_server']['bbb_base_url'] = array(
    '#title' => t('Base URL'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_base_url', BBB_API_BASE_URL),
    '#description' => t('The URL that points to your instance of Big Blue Button.'),
  );
  $form['bbb_server']['bbb_security_salt'] = array(
    '#title' => t('Security Salt'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_security_salt', BBB_API_SECURITY_SALT),
    '#description' => t('The predefinde security salt. This is a server side configuration option check the Big Blue Button !documentation', array('!documentation' => l(t('documentation'), 'http://code.google.com/p/bigbluebutton/'))),
  );
  $form['bbb_client'] = array(
    '#title' => t('Client settings'),
    '#type' => 'fieldset',
  );
  $form['bbb_client']['bbb_display_mode'] = array(
    '#title' => t('Display mode'),
    '#type' => 'radios',
    '#options' => array(
      'inline' => t('Display inline'),
      'blank' => t('Display in a new window'),
    ),
    '#default_value' => variable_get('bbb_display_mode', BBB_DISPLAY_MODE),
    '#description' => t('Choose wether to display the meeting inline or in a new window.'),
  );
  $form['bbb_client']['bbb_display_height'] = array(
    '#title' => t('Height x Width'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_display_height', BBB_DISPLAY_HEIGHT),
    '#prefix' => '<div class="container-inline">',
    '#suffix' => 'x',
    '#size' => 4,
  );
  $form['bbb_client']['bbb_display_width'] = array(
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_display_width', BBB_DISPLAY_WIDTH),
    '#suffix' => '</div>',
    '#size' => 4,
    '#description' => '<br />' . t('Give dimensions for inline display, e.g. <em>520px</em> x <em>100%</em>.'),
  );
  $form['connection'] = array(
    '#type' => 'submit',
    '#executes_submit_callback' => FALSE,
    '#value' => t('Test Connection'),
  );
  return system_settings_form($form);
}

/**
 * Test conection to Big Blue Button
 */
function bbb_test_connection($base_url, $security_salt) {
  // Generate a random value
  $params = array('random' => user_password());
  // Generate query with form data
  $query_string = bbb_api_generate_querystring(BBB_API_GET_MEETINGS, $params, FALSE);
  $query_string = $query_string . '&checksum=' . sha1($query_string . $security_salt);
  $request = $base_url . BBB_API_GET_MEETINGS . '?' . $query_string;
  bbb_api_debug($request);
  $xml = @simplexml_load_file($request);
  $response = bbb_api_parse_response($xml);
  bbb_api_debug($response);

  if ($response->returncode == 'SUCCESS') {
    drupal_set_message(t('The connection has been established succesfully. Please save your configuration now.'));
  }
  else {
    drupal_set_message(t('The connection could not be established correctly. The server response was: %message.', array('%message' => ($response->message ? $response->message : t('No response')))), 'error');
    watchdog('big blue button', '%message', array('%message' => $response->message), WATCHDOG_ERROR);
    return FALSE;
  }
}
