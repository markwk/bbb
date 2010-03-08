<?php
// $Id$

/**
 * @file
 * BigBlueButton - Enables universities and colleges to deliver a high-quality
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
  $form = array();
  $form['bbb_service'] = array(
    '#title' => 'Server settings',
    '#type' => 'fieldset',
    '#description' => t('Adjust the default server settings. Read more about BigBlueButton on !home. See the documentation for !documentation', array('!home' => l(t('BigBlueButton.org'), 'http://bigbluebutton.org/'), '!documentation' => l(t('installation instructions'), 'http://code.google.com/p/bigbluebutton/'))),
  );
  $form['bbb_service']['bbb_base_url'] = array(
    '#title' => t('Base URL'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_base_url', BIGBLUEBUTTON_BASE_URL),
    '#description' => t('The URL that points to your instance of BigBlueButton.'),
  );
  $form['bbb_service']['bbb_security_salt'] = array(
    '#title' => t('Security Salt'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_security_salt', BIGBLUEBUTTON_SECURITY_SALT),
    '#description' => t('The predefinde security salt. This is a server side configuration option check the BigBlueButton !documentation', array('!documentation' => l(t('documentation'), 'http://code.google.com/p/bigbluebutton/'))),
  );
  $form['bbb_default'] = array(
    '#title' => 'Default settings',
    '#type' => 'fieldset',
    '#description' => t('You may provide default settings for nodes associated with BigBlueButton.'),
  );
  $form['bbb_default']['bbb_default_welcome'] = array(
    '#title' => t('Welcome message'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_default_welcome', ''),
    '#description' => t('A welcome message that gets displayed on the chat window when the participant joins. You can include keywords (%%CONFNAME%%, %%DIALNUM%%, %%CONFNUM%%) which will be substituted automatically.'),
  );
  $form['bbb_default']['bbb_default_dialNumber'] = array(
    '#title' => t('Dial number'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_default_dialNumber', ''),
    '#description' => t('The dial access number that participants can call in using regular phone.'),
  );
  $form['bbb_default']['bbb_default_dialNumber'] = array(
    '#title' => t('Dial number'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_default_dialNumber', ''),
    '#description' => t('The dial access number that participants can call in using regular phone.'),
  );
  $form['bbb_default']['bbb_default_logoutURL'] = array(
    '#title' => t('Logout URL'),
    '#type' => 'textfield',
    '#default_value' => variable_get('bbb_default_logoutURL', ''),
    '#description' => t('The dial access number that participants can call in using regular phone.'),
  );
  return system_settings_form($form);
}
