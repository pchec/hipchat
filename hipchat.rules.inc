<?php
/**
 * @file
 * HipChat integration module rules functions.
 */

/**
 * Implements hook_rules_action_info().
 */
function hipchat_rules_action_info() {
  $actions = array();
  $actions['hipchat_send_message'] = array(
    'base' => 'hipchat_rules_send_message_action',
    'label' => t('Send message in HipChat'),
    'group' => t('HipChat'),
    'parameter' => array(
      'message' => array(
        'type' => 'text',
        'label' => t('Message to be sent.'),
      ),
      'room' => array(
        'type' => 'integer',
        'label' => t('Room'),
        'description' => t('ID of the room where the message should appear. If not provided, site default is used.'),
        'optional' => TRUE,
      ),
      'access_token' => array(
        'type' => 'text',
        'label' => t('Access token'),
        'description' => t('Access token for the room. If not provided, site default is used.'),
        'optional' => TRUE,
      ),
    ),
  );
  $actions['hipchat_create_user'] = array(
    'base' => 'hipchat_rules_create_user_action',
    'label' => t('Create a user in HipChat'),
    'group' => t('HipChat'),
    'parameter' => array(
      'name' => array(
        'type' => 'text',
        'label' => t('Name'),
      ),
      'email' => array(
        'type' => 'text',
        'label' => t('Email'),
      ),
      'password' => array(
        'type' => 'text',
        'label' => t('Password'),
        'optional' => TRUE,
      ),
    ),
  );
  $actions['hipchat_update_user'] = array(
    'base' => 'hipchat_rules_update_user_action',
    'label' => t('Update a user in HipChat'),
    'group' => t('HipChat'),
    'parameter' => array(
      'current_email' => array(
        'type' => 'text',
        'label' => t('Current email'),
      ),
      'new_email' => array(
        'type' => 'text',
        'label' => t('New email'),
        'optional' => TRUE,
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('Name'),
        'optional' => TRUE,
      ),
      'title' => array(
        'type' => 'text',
        'label' => t('Title'),
        'optional' => TRUE,
      ),
      'password' => array(
        'type' => 'text',
        'label' => t('Password'),
        'optional' => TRUE,
      ),
      'mention_name' => array(
        'type' => 'text',
        'label' => t('Mention name'),
        'optional' => TRUE,
      ),
    ),
  );
  $actions['hipchat_delete_user'] = array(
    'base' => 'hipchat_rules_delete_user_action',
    'label' => t('Delete a user from HipChat'),
    'group' => t('HipChat'),
    'parameter' => array(
      'id' => array(
        'type' => 'text',
        'label' => t('HipChat user ID or email'),
      ),
    ),
  );
  $actions['hipchat_get_user_data'] = array(
    'base' => 'hipchat_rules_get_user_data_action',
    'label' => t('Get data from HipChat user profile'),
    'group' => t('HipChat'),
    'parameter' => array(
      'id' => array(
        'type' => 'text',
        'label' => t('HipChat user ID or email'),
      ),
    ),
    'provides' => array(
      'id' => array(
        'type' => 'integer',
        'label' => t('User ID'),
      ),
      'name' => array(
        'type' => 'text',
        'label' => t('User name'),
      ),
      'email' => array(
        'type' => 'text',
        'label' => t('User email'),
      ),
      'title' => array(
        'type' => 'text',
        'label' => t('User title'),
        'optional' => TRUE,
      ),
      'is_deleted' => array(
        'type' => 'boolean',
        'label' => t('User deleted'),
      ),
      'mention_name' => array(
        'type' => 'text',
        'label' => t('Mention name'),
      ),
    ),
  );
  return $actions;
}

/**
 * Rules action for sending a message to HipChat.
 */
function hipchat_rules_send_message_action($message, $room, $access_token) {
  if (!$room) {
    $room = variable_get('hipchat_default_room', NULL);
  }
  hipchat_send($message, $room, $access_token);
}

/**
 * Rules action for creating a user in HipChat.
 */
function hipchat_rules_create_user_action($name, $email, $password = null) {
  if (!empty($password)) {
    hipchat_create_user($name, $email, $password);
  } else {
    hipchat_create_user($name, $email);
  }
}

/**
 * Rules action for creating a user in HipChat.
 */
function hipchat_rules_update_user_action($current_email, $new_email = null, $name = null, $title = null, $password = null, $mention_name = null) {
  if (!empty($current_email)) {
    $updates = array();
    if (!empty($new_email)) {
      $updates['email'] = $new_email;
    }
    if (!empty($name)) {
      $updates['name'] = $name;
    }
    if (!empty($password)) {
      $updates['password'] = $password;
    }
    if (!empty($mention_name)) {
      $updates['mention_name'] = $mention_name;
    }
    if (!empty($title)) {
      $updates['title'] = $title;
    }
    hipchat_update_user($current_email, $updates);
  }
}

/**
 * Rules action for deleting a user from HipChat.
 */
function hipchat_rules_delete_user_action($id_or_email) {
  hipchat_delete_user($id_or_email);
}

/**
 * Rules action for getting data from HipChat user profile.
 */
function hipchat_rules_get_user_data_action($id_or_email) {
  return hipchat_get_user($id_or_email);
}
