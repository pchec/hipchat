<?php
/**
 * @file
 * HipChat module form for sending a message.
 */

/**
 * HipChat test message form.
 */
function hipchat_send_test_message_form($form, &$form_state) {
  $form['hipchat_test_room'] = array(
    '#type' => 'textfield',
    '#title' => t('Room'),
    '#default_value' => variable_get('hipchat_default_room'),
  );
  $form['hipchat_test_token'] = array(
    '#type' => 'textfield',
    '#title' => t('Token'),
    '#default_value' => variable_get('hipchat_token'),
  );
  $form['hipchat_test_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send message'),
  );
  return $form;
}

/**
 * Submit handler for HipChat test message form.
 */
function hipchat_send_test_message_form_submit($form, &$form_state) {
  $room = $form_state['values']['hipchat_test_room'];
  $token = $form_state['values']['hipchat_test_token'];
  $message = $form_state['values']['hipchat_test_message'];
  hipchat_send($message, $room, $token);
}
