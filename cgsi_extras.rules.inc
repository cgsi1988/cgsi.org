<?php

/**
 * @file
 * Rules hooks for cgsi_extras.module.
 */
/**
 * Implements hook_rules_action_info().
 */
// function cgsi_extras_rules_action_info() {
//     // Standardize revocation date
//     $actions['cgsi_extras_standardize_revocation_date'] = array(
//                     'label' => t('Standardize revocation date.'),
//                     'group' => t('Expiration'),
//                     'base' => 'cgsi_extras_standardize_revocation_date',
//                     'parameter' => array(
//                                     'account' => array(
//                                                     'type' => 'user',
//                                                     'label' => t('User'),
//                                     ),
//                                     'expiration' => array(
//                                                     'type' => 'uc_roles_expiration',
//                                                     'label' => t('Role expiration'),
//                                     ),
//                     ),
//     );
//     return $actions;
// }

/**
 * Implements hook_rules_event_info().
 */
// function cgsi_extras_rules_event_info() {
//     $account = array(
//                     'type' => 'user',
//                     'label' => t('User'),
//     );
//     $expiration = array(
//                     'type' => 'uc_roles_expiration',
//                     'label' => t('Role expiration'),
//     );

//     $events['cgsi_extras_role_granted'] = array(
//                     'label' => t('Role is granted'),
//                     'group' => t('Membership'),
//                     'variables' => array(
//                                     'account' => $account,
//                                     'expiration' => $expiration,
//                     ),
//     );
//     return $events;
// }

// /**
//  * Options list callback for message formats.
//  */
// function cgsi_extras_message_formats() {
//   global $user;

//   $options = array();
//   $formats = filter_formats($user);
//   foreach ($formats as $format) {
//     $options[$format->format] = $format->name;
//   }

//   return $options;
// }
/**
 * Implements hook_rules_data_info().
 *
 * An entity is defined in order to get role expiration tokens in the email.
 */
// function cgsi_extras_rules_data_info() {
//   // CA entity for a role expiration object.
//   $entities['uc_roles_expiration'] = array(
//     'label' => t('Ubercart role expiration'),
//     'wrap' => TRUE,
//     'token type' => 'uc_role',
//     'property info' => array(
//       'reid' => array(
//         'type' => 'integer',
//         'label' => t('Role expiration ID'),
//         'description' => t('Primary key for role expirations.'),
//       ),
//       'uid' => array(
//         'type' => 'integer',
//         'label' => t('User ID'),
//         'description' => t('The user account ID.'),
//       ),
//       'user' => array(
//         'type' => 'user',
//         'label' => t('User'),
//         'description' => t('The user account that has the role.'),
//         'getter callback' => 'uc_roles_get_expiration_properties',
//         'setter callback' => 'uc_roles_set_expiration_properties',
//       ),
//       'rid' => array(
//         'type' => 'integer',
//         'label' => t('Role ID'),
//         'description' => t('The granted role.'),
//       ),
//       'expiration' => array(
//         'type' => 'date',
//         'label' => t('Expiration time'),
//         'description' => t('The time the role will be removed from the user.'),
//       ),
//       'notified' => array(
//         'type' => 'boolean',
//         'label' => t('Notified'),
//         'description' => t('Indicates the user has been warned that the role will be removed soon.'),
//       ),
//     ),
//   );

//   return $entities;
// }

// /**
//  * Callback for getting role expiration properties.
//  *
//  * @see entity_metadata_node_entity_info_alter()
//  */
// function cgsi_extras_get_expiration_properties($expiration, array $options, $name, $entity_type) {
//   switch ($name) {
//     case 'user':
//       return $expiration->uid;
//   }
// }

// /**
//  * Callback for setting role expiration properties.
//  *
//  * @see entity_metadata_node_entity_info_alter()
//  */
// function cgsi_extras_set_expiration_properties($expiration, $name, $value) {
//   if ($name == 'user') {
//     $expiration->uid = $value;
//   }
// }



// /**
//  * Send an email with order and role replacement tokens.
//  *
//  * The recipients, subject, and message fields take order token replacements.
//  *
//  * @see uc_roles_action_order_email_form()
//  */
// function cgsi_extras_action_order_email($order, $role_expiration, $from, $addresses, $subject, $message, $format) {
//   $settings = array(
//     'from' => $from,
//     'addresses' => $addresses,
//     'subject' => $subject,
//     'message' => $message,
//     'format' => $format,
//   );
//   // Token replacements for the subject and body
//   $settings['replacements'] = array(
//     'uc_order' => $order,
//     'uc_role' => $role_expiration,
//   );

//   // Replace tokens and parse recipients.
//   $recipients = array();
//   $addresses = token_replace($settings['addresses'], $settings['replacements']);
//   foreach (explode("\n", $addresses) as $address) {
//     $address = trim($address);
//     // Remove blank lines
//     if (!empty($address)) {
//       $recipients[] = $address;
//     }
//   }

//   // Send to each recipient.
//   foreach ($recipients as $email) {
//     $sent = drupal_mail('uc_order', 'action-mail', $email, uc_store_mail_recipient_language($email), $settings, $settings['from']);

//     if (!$sent['result']) {
//       watchdog('uc_roles', 'Attempt to e-mail @email concerning order @order_id failed.', array('@email' => $email, '@order_id' => $order->order_id), WATCHDOG_ERROR);
//     }
//   }
// }

// /**
//  * Send an email with order and role replacement tokens.
//  *
//  * The recipients, subject, and message fields take order token replacements.
//  *
//  * @see uc_roles_action_user_email_form()
//  */
// function cgsi_extras_action_user_email($account, $role_expiration, $from, $addresses, $subject, $message, $format) {
//   $settings = array(
//     'from' => $from,
//     'addresses' => $addresses,
//     'subject' => $subject,
//     'message' => $message,
//     'format' => $format,
//   );
//   // Token replacements for the subject and body
//   $settings['replacements'] = array(
//     'user' => $account,
//     'uc_role' => $role_expiration,
//   );

//   // Replace tokens and parse recipients.
//   $recipients = array();
//   $addresses = token_replace($settings['addresses'], $settings['replacements']);
//   foreach (explode("\n", $addresses) as $address) {
//     $address = trim($address);
//     // Remove blank lines
//     if (!empty($address)) {
//       $recipients[] = $address;
//     }
//   }

//   // Send to each recipient.
//   foreach ($recipients as $email) {
//     $sent = drupal_mail('uc_order', 'action-mail', $email, uc_store_mail_recipient_language($email), $settings, $settings['from'], false);

//     if (!$sent['result']) {
//       watchdog('uc_roles', 'Attempt to e-mail @email concerning role notification failed.', array('@email' => $email), WATCHDOG_ERROR);
//     }
//   }
// }

// /**
//  * Renews an order's product roles.
//  *
//  * This function updates expiration time on all roles found on all products
//  * on a given order. First, the order user is loaded, then the order's products
//  * are scanned for role product features. If any are found, the expiration time
//  * of the role is set using the feature settings to determine the new length of
//  * time the new expiration will last. An order comment is saved, and the user
//  * is notified in Drupal, as well as through the email address associated with
//  * the order.
//  *
//  * @param $order
//  *   An Ubercart order object.
//  * @param $message
//  *   If TRUE, messages will be displayed to the user about the renewal.
//  */
// function cgsi_extras_action_order_renew($order, $message) {
//   // Load the order's user and exit if not available.
//   if (!($account = user_load($order->uid))) {
//     return;
//   }

//   // Loop through all the products on the order.
//   foreach ($order->products as $product) {
//     // Look for any role promotion features assigned to the product.
//     $roles = db_query("SELECT * FROM {uc_roles_products} WHERE nid = :nid", array(':nid' => $product->nid));

//     foreach ($roles as $role) {
//       // Product model matches, or was 'any'.
//       if (!empty($role->model) && $role->model != $product->model) {
//         continue;
//       }

//       $existing_role = db_query("SELECT * FROM {uc_roles_expirations} WHERE uid = :uid AND rid = :rid", array(':uid' => $account->uid, ':rid' => $role->rid))->fetchObject();

//       // Determine the expiration timestamp for the role.
//       $expiration = _uc_roles_product_get_expiration($role, $product->qty, isset($existing_role->expiration) ? $existing_role->expiration : NULL);

//       // Leave an order comment.
//       if (isset($existing_role->expiration)) {
//         $op = 'renew';
//         $comment = t('Customer user role %role renewed.', array('%role' => _uc_roles_get_name($role->rid)));

//         // Renew the user's role.
//         uc_roles_renew($account, $role->rid, $expiration, !$message);
//       }
//       else {
//         $op = 'grant';
//         $comment = t('Customer granted user role %role.', array('%role' => _uc_roles_get_name($role->rid)));

//         // Grant the role to the user.
//         uc_roles_grant($account, $role->rid, $expiration, TRUE, !$message);
//       }

//       // Get the new expiration (if applicable)
//       $new_expiration = db_query("SELECT * FROM {uc_roles_expirations} WHERE uid = :uid AND rid = :rid", array(':uid' => $account->uid, ':rid' => $role->rid))->fetchObject();
//       if (!$new_expiration) {
//         $new_expiration = new stdClass();
//         $new_expiration->uid = $account->uid;
//         $new_expiration->rid = $role->rid;
//         $new_expiration->expiration = NULL;
//       }

//       uc_order_comment_save($order->order_id, $account->uid, $comment);

//       // Trigger role email.
//       rules_invoke_event('uc_roles_notify_' . $op, $order, $new_expiration);
//     }
//   }
// }
