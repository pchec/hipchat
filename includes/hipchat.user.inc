<?php
/**
 * @file
 * Functions allowing users to alter the user settings and options.
 */

/**
 * Form constructor for the user jabber registration form.
 *
 * @param string $account
 *   The account information for the user page being viewed.
 *
 * @see hipchat_user_form_validate()
 * @see hipchat_user_form_submit()
 *
 * @ingroup forms
 */
function hipchat_user_form($form, &$form_state, $account) {
  global $user;
  
  if (!isset($form_state['user'])) {
    $form_state['user'] = $account;
  }
  else {
    $account = $form_state['user'];
  }

  $uid = $account->uid;
  $form['hipchat']['info'] = array(
    '#type' => 'item',
    '#title' => t('Register for a HipChat account.'),
    '#description' => t('<a href="@hipchat_url" target="_blank">HipChat</a> is our group chat solution.<br />Log in to HipChat here: <a href="@hipchat_url" target="_blank">@hipchat_url</a><br />Your login is your email address.<br />You can set your password below. You need to do it before logging in for the first time.<br />', array(
      '@hipchat_url' => variable_get('hipchat_url','https://www.hipchat.com'),
    )),
    '#weight' => 0,
  );

  $form['hipchat']['password'] = array(
    '#type' => 'password',
    '#title' => t('Set Password'),
    '#description' => t('If you have already created a HipChat account with us, providing a new password here will reset it for you.'),
    '#required' => TRUE,
    '#size' => 60,
    '#maxlength' => 50,
    '#weight' => 20,
    '#default_value' => '',
  );

  $form['submit_button'] = array(
    '#type' => 'submit',
    '#value' => t('Register'),
  );

  $form['#validate'] = array('hipchat_user_form_validate');
  $form['#submit'] = array('hipchat_user_form_submit');
  return $form;
}

/**
 * Form validation handler for hipchat_user_form().
 *
 * @see hipchat_user_form_submit()
 */
function hipchat_user_form_validate($form, &$form_state) {
  $account = $form_state['user'];
  $uid = $account->uid;

  if (strlen($form_state['values']['password']) < 8) {
    form_set_error('password', t('Password has to be at least 8 characters long.'));
  }
}

/**
 * Form submission handler for hipchat_user_form().
 *
 * @see hipchat_user_form_validate()
 */
function hipchat_user_form_submit($form, &$form_state) {
  $account = $form_state['user'];
	$password = (string) $form_state['values']['password'];
  $hc_user_data = hipchat_get_user($account->mail);
  if (empty($hc_user_data)) {
    hipchat_create_user($account->name, $account->mail, $password);
  } elseif ($hc_user_data['is_deleted'] == true) {
    hipchat_create_user($account->mail, $password);
  } else {
    hipchat_sync_user($account, $password);
  } 
}
