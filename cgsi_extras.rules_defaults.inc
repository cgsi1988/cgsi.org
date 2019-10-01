<?php

/**
 * @file
 * Default Rules configurations for cgsi_extras.module.
 */

/**
 * Implements hook_default_rules_configuration().
 */
// function cgsi_extras_default_rules_configuration() {
//     $configs = array();

//     $user_args = array(
//                     'account:select' => 'account',
//                     'expiration:select' => 'expiration',
//     );

//     // Set the revocation date for granted role to a standardized date/time
//     $rule = rules_reaction_rule();
//     $rule->label = t('Standardize Role Revocation Date');
//     $rule->active = TRUE;
//     $rule->event('uc_roles_notify_grant');
//     $rule->action('cgsi_extras_standardize_revocation_date', $user_args);
//     $configs['cgsi_extras_role_granted'] = $rule;

//     return $configs;
// }