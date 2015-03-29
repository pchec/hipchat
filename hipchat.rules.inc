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
      'user' => array(
        'type' => 'user',
        'label' => t('Created user'),
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
      'user' => array(
        'type' => 'user',
        'label' => t('Updated user'),
      ),
      'password' => array(
        'type' => 'text',
        'label' => t('New password'),
        'optional' => TRUE,
      ),
      'current_email' => array(
        'type' => 'text',
        'label' => t('Old email'),
        'optional' => TRUE,
      ),
    ),
  );
  $actions['hipchat_delete_user'] = array(
    'base' => 'hipchat_rules_delete_user_action',
    'label' => t('Delete a user from HipChat'),
    'group' => t('HipChat'),
    'parameter' => array(
      'user' => array(
        'type' => 'user',
        'label' => t('User to be deleted'),
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
  $actions['hipchat_delete_user_from_room'] = array(
    'base' => 'hipchat_rules_delete_user_from_room_action',
    'label' => t('Delete user from a room'),
    'group' => t('HipChat'),
    'parameter' => array(
      'room_id_or_name' => array(
        'type' => 'text',
        'label' => t('HipChat room ID or name'),
      ),
      'user_id_or_email' => array(
        'type' => 'text',
        'label' => t('HipChat user ID or email'),
      ),
    ),
  );
  $actions['hipchat_add_user_to_room'] = array(
    'base' => 'hipchat_rules_add_user_to_room_action',
    'label' => t('Add user to a room'),
    'group' => t('HipChat'),
    'parameter' => array(
      'room_id_or_name' => array(
        'type' => 'text',
        'label' => t('HipChat room ID or name'),
      ),
      'user_id_or_email' => array(
        'type' => 'text',
        'label' => t('HipChat user ID or email'),
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
function hipchat_rules_create_user_action($user, $password = null) {
  if (!empty($password)) {
    hipchat_create_user($user, $password);
  } else {
    hipchat_create_user($user);
  }
}

/**
 * Rules action for updating a user in HipChat.
 */
function hipchat_rules_update_user_action($user, $password = null, $old_email = null) {
  hipchat_sync_user($user, $password, $old_email);
}

/**
 * Rules action for deleting a user from HipChat.
 */
function hipchat_rules_delete_user_action($user) {
  hipchat_delete_user($user);
}

/**
 * Rules action for getting data from HipChat user profile.
 */
function hipchat_rules_get_user_data_action($id_or_email) {
  return hipchat_get_user($id_or_email);
}

/**
 * Rules action for adding a user to a HipChat room.
 */
function hipchat_rules_add_user_to_room_action($room_id_or_name, $user_id_or_email) {
  hipchat_add_user_to_room($room_id_or_name, $user_id_or_email);
}

/**
 * Rules action for deleting a user from a HipChat room.
 */
function hipchat_rules_delete_user_from_room_action($room_id_or_name, $user_id_or_email) {
  hipchat_delete_user_from_room($room_id_or_name, $user_id_or_email);
}

/**
* Implementation of hook_rules_event_info().
* @ingroup rules
*/
function hipchat_rules_event_info() {
  return array(
    'hipchat_user_registered' => array(
      'label' => t('User registered in HipChat'),
      'module' => 'hipchat',
      'group' => t('HipChat'),
      'variables' => array(
        'account' => array('type' => 'user', 'label' => t('The user who registered.')),
      ),
    ),
    'hipchat_user_deleted' => array(
      'label' => t('User deleted from HipChat'),
      'module' => 'hipchat',
      'group' => t('HipChat'),
      'variables' => array(
        'account' => array('type' => 'user', 'label' => t('The user who was deleted.')),
      ),
    ),
  );
}