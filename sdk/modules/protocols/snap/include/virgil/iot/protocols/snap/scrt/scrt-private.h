//  Copyright (C) 2015-2020 Virgil Security, Inc.
//
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      (1) Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//      (2) Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in
//      the documentation and/or other materials provided with the
//      distribution.
//
//      (3) Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
//  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
//  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
//  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
//  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
//  IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.
//
//  Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>


#ifndef VS_SECURITY_SDK_SNAP_SERVICES_SCRT_PRIVATE_H
#define VS_SECURITY_SDK_SNAP_SERVICES_SCRT_PRIVATE_H

#include <virgil/iot/protocols/snap/scrt/scrt-server.h>
#include <virgil/iot/protocols/snap/scrt/scrt-structs.h>
#include <virgil/iot/protocols/snap.h>
#include <virgil/iot/status_code/status_code.h>
#include <virgil/iot/trust_list/trust_list.h>
#include <virgil/iot/trust_list/tl_structs.h>
#include <virgil/iot/protocols/snap/snap-structs.h>
#include <virgil/iot/provision/provision-structs.h>

// mute "error: multi-character character constant" message
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmultichar"
typedef enum { VS_SCRT_SERVICE_ID = HTONL_IN_COMPILE_TIME('SCRT') } vs_scrt_t;

#define SCRT_NONCE_SZ (32)

typedef enum {
    VS_SCRT_INFO = HTONL_IN_COMPILE_TIME('INFO'), /* Get crypto information */
    VS_SCRT_GSEK = HTONL_IN_COMPILE_TIME('GSEK'), /* Get SEssion Key */
    VS_SCRT_AUSR = HTONL_IN_COMPILE_TIME('AUSR'), /* Add device User */
    VS_SCRT_RUSR = HTONL_IN_COMPILE_TIME('RUSR'), /* Remove device User */
    VS_SCRT_GUSR = HTONL_IN_COMPILE_TIME('GUSR'), /* Get Users */
} vs_snap_scrt_element_e;
#pragma GCC diagnostic pop

typedef struct __attribute__((__packed__)) {
    uint16_t signature_sz;          /**< Size of vs_sign_t  */
    uint16_t key_sz;                /**< Size of vs_pubkey_dated_t */
    uint8_t raw_sign_datedpubkey[]; /**< Array that contains vs_sign_t and vs_pubkey_dated_t. Because of variable sizes. */
} vs_scrt_signed_key_t;

// --------------------------------------------------------
//      SCRT::INFO - Get crypto information
// --------------------------------------------------------
// INFO: Could be sent in a plain text
typedef struct __attribute__((__packed__)) {
    uint8_t provisioned;             /**< Current version of protocol */
    vs_scrt_signed_key_t signed_key; /**< Peer key and its signature */
} vs_scrt_info_response_t;

// --------------------------------------------------------
//      SCRT::GSEK - Get SEssion Key
// --------------------------------------------------------
// INFO: Must be encrypted asymmetrically
typedef struct __attribute__((__packed__)) {
    uint8_t nonce[SCRT_NONCE_SZ];   /**< nonce to protect against reply attacks */
    uint8_t raw_sign_datedpubkey[]; /**< Array that contains vs_sign_t and vs_pubkey_dated_t. Because of variable sizes. */
} vs_scrt_gsek_request_t;

// INFO: Must be encrypted asymmetrically
typedef struct __attribute__((__packed__)) {
    uint8_t requested_nonce[SCRT_NONCE_SZ];   /**< a copy of nonce from request */
    uint8_t session_key[SCRT_SESSION_KEY_SZ]; /**< Session key. The simplest solution for ver.1 */
} vs_scrt_gsek_response_t;

// --------------------------------------------------------
//      SCRT::AUSR - Add a new User
// --------------------------------------------------------
// INFO: Must be encrypted asymmetrically
typedef struct __attribute__((__packed__)) {
    uint8_t user_type;                              /**< #vs_user_type_t */
    uint8_t new_user_name[SCRT_USER_NAME_SZ_MAX];   /**< New User name */
    uint16_t new_user_crypto_info;                  /**< Size of vs_scrt_signed_key_t for new user */
    uint16_t current_owner_crypto_info;             /**< Size of vs_scrt_signed_key_t for current owner */
    uint8_t signed_keys[];                          /**< vs_scrt_signed_key_t of a New and a current owners */
} vs_scrt_ausr_request_t;

// --------------------------------------------------------
//      SCRT::RUSR - Remove user
// --------------------------------------------------------
// INFO: Must be encrypted asymmetrically
typedef struct __attribute__((__packed__)) {
    uint8_t user_type;                              /**< #vs_user_type_t */
    uint8_t rm_user_name[SCRT_USER_NAME_SZ_MAX];    /**< Name of User to be removed */
    vs_scrt_signed_key_t current_owner_crypto_info; /**< Crypto info about a current owner */
} vs_scrt_rusr_request_t;

// --------------------------------------------------------
//      SCRT::GUSR - Get users
// --------------------------------------------------------
typedef struct __attribute__((__packed__)) {
    uint8_t user_name[SCRT_USER_NAME_SZ_MAX];   /**< New name */
    vs_pubkey_t user_pub_key;                   /**< Public key of user */
} vs_scrt_gusr_tiny_t;

// INFO: Could be sent in a plain text
typedef struct __attribute__((__packed__)) {
    uint8_t user_type;                              /**< #vs_user_type_t */
    uint8_t max_users_per_resp;                     /**< Maximum users in response */
    uint8_t users_offset;                           /**< First user num to get */
} vs_scrt_gusr_request_t;

// INFO: Could be sent in a plain text
typedef struct __attribute__((__packed__)) {
    uint8_t user_type;                              /**< #vs_user_type_t */
    uint8_t users_in_resp;                          /**< Amount of users in response */
    uint8_t users_offset;                           /**< First user num */
    vs_scrt_gusr_tiny_t users[];                    /**< Array of #vs_scrt_gusr_tiny_t. Amount is #users_in_resp */
} vs_scrt_gusr_response_t;

#endif // VS_SECURITY_SDK_SNAP_SERVICES_SCRT_PRIVATE_H
