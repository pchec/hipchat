<?php
/**
 * Form for the HipChat admin page.
 */
function hipchat_admin_form() {
  $form['hipchat_url'] = array(
    '#type' => 'textfield',
    '#title' => t('HipChat URL'),
    '#description' => t('Enter the URL to your HipChat.'),
    '#default_value' => variable_get('hipchat_url', NULL),
  );
  $form['hipchat_admin_token'] = array(
    '#type' => 'textfield',
    '#title' => t('HipChat management token'),
    '#description' => t('Get an personal API token from !hipchat_link. You must have administrative privileges for the API calls to work.'
      , array('!hipchat_link' => l(t('your HipChat admin page'), 'https://www.hipchat.com/account/api'))),
    '#default_value' => variable_get('hipchat_admin_token', NULL),
  );
  $form['hipchat_token'] = array(
    '#type' => 'textfield',
    '#title' => t('HipChat default message token'),
    '#description' => t('Get a personal API token from !hipchat_link or get a room-specific token by creating an !integration.', 
			array(
				'!hipchat_link' => l(t('your HipChat admin page'), 'https://www.hipchat.com/account/api'),
				'!integration' => l(t('integration'), 'https://www.hipchat.com/admin/byo'),
				)
		),
    '#default_value' => variable_get('hipchat_token', NULL),
  );
  $form['hipchat_default_room'] = array(
    '#type' => 'textfield',
    '#title' => t('HipChat default room'),
    '#description' => t('Enter the default room to send notices.'),
    '#default_value' => variable_get('hipchat_default_room', NULL),
  );

  return system_settings_form($form);
}
