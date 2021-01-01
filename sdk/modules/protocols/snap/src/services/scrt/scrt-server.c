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

 #define SCRT_SERVER 1

#if SCRT_SERVER

#include <virgil/iot/protocols/snap/scrt/scrt-server.h>
#include <virgil/iot/protocols/snap/scrt/scrt-private.h>
#include <virgil/iot/protocols/snap/scrt/scrt-structs.h>
#include <virgil/iot/protocols/snap/generated/snap_cvt.h>
#include <virgil/iot/protocols/snap.h>
#include <virgil/iot/status_code/status_code.h>
#include <virgil/iot/logger/logger.h>
#include <virgil/iot/macros/macros.h>
#include <virgil/iot/users/users.h>
#include <virgil/iot/secmodule/secmodule-helpers.h>
#include <stdlib-config.h>
#include <endian-config.h>

static vs_secmodule_impl_t *_secmodule = NULL;
static vs_snap_scrt_server_service_t _impl = {};
static bool _scrt_service_ready = false;

/******************************************************************/
static vs_status_e
_scrt_info_request_processor(const uint8_t *request,
                             const uint16_t request_sz,
                             uint8_t *response,
                             const uint16_t response_buf_sz,
                             uint16_t *response_sz) {
    uint16_t cert_buf_sz;
    uint16_t owners_amount;
    vs_status_e ret_code;

    // Check input parameters
    CHECK_NOT_ZERO_RET(response, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_RET(response_buf_sz >= sizeof(vs_scrt_info_response_t),
              VS_CODE_ERR_INCORRECT_ARGUMENT,
              "Unsupported request structure vs_scrt_info_response_t");

    // Calculate buffer size
    cert_buf_sz = response_buf_sz - sizeof(vs_scrt_info_response_t);

    // Fill data
    vs_scrt_info_response_t *info_data = (vs_scrt_info_response_t *)response;
    info_data->provisioned = vs_provision_is_ready();
    STATUS_CHECK_RET(vs_users_get_amount(VS_USER_OWNER, &owners_amount), "Cannot get amount of owners");
    info_data->owners_count = owners_amount;
    STATUS_CHECK_RET(vs_provision_own_cert(&info_data->own_cert, cert_buf_sz), "Cannot load own certificate");

    *response_sz = sizeof(vs_scrt_info_response_t) + info_data->own_cert.key_sz + info_data->own_cert.signature_sz;

    return VS_CODE_OK;
}

/******************************************************************/
static vs_status_e
_verify_owner_cert(const vs_provision_cert_t *cert) {
    vs_status_e ret_code;
    char name[USER_NAME_SZ_MAX];

    STATUS_CHECK_RET(vs_provision_verify_cert(cert), "Wrong owner's certificate");

    STATUS_CHECK_RET(vs_users_get_name(VS_USER_OWNER,
                                       (vs_pubkey_dated_t*)cert->raw_cert,
                                       name, USER_NAME_SZ_MAX),
                     "Cannot find required owner");

    VS_LOG_DEBUG("Verified user: %s", name);

    return VS_CODE_OK;
}

/******************************************************************/
static vs_status_e
_scrt_get_session_key_request_processor(const uint8_t *request,
                                        const uint16_t request_sz,
                                        uint8_t *response,
                                        const uint16_t response_buf_sz,
                                        uint16_t *response_sz) {
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************/
static vs_status_e
_scrt_add_user_request_processor(const uint8_t *request,
                                 const uint16_t request_sz,
                                 uint8_t *response,
                                 const uint16_t response_buf_sz,
                                 uint16_t *response_sz) {
    vs_status_e ret_code;
    const vs_scrt_ausr_request_t *add_user_info = (const vs_scrt_ausr_request_t *)request;
    const vs_provision_cert_t *owner_cert;
    const vs_provision_cert_t *new_user_cert;
    size_t new_user_name_sz;
    char found_name[USER_NAME_SZ_MAX];

    // Check input parameters
    CHECK_NOT_ZERO_RET(request, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_RET(request_sz > sizeof(vs_scrt_ausr_request_t),
              VS_CODE_ERR_INCORRECT_ARGUMENT,
              "Unsupported request structure vs_scrt_ausr_request_t");
    CHECK_NOT_ZERO_RET(add_user_info->new_user_cert_sz, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_NOT_ZERO_RET(add_user_info->current_owner_cert_sz, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_NOT_ZERO_RET(add_user_info->user_type < VS_USER_TYPE_MAX, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_NOT_ZERO_RET(add_user_info->new_user_name[0], VS_CODE_ERR_INCORRECT_ARGUMENT);
    new_user_name_sz = strnlen((const char *)add_user_info->new_user_name, USER_NAME_SZ_MAX);
    CHECK_NOT_ZERO_RET(new_user_name_sz < USER_NAME_SZ_MAX, VS_CODE_ERR_INCORRECT_ARGUMENT);

    // Fill cert pointers
    new_user_cert = (const vs_provision_cert_t *)add_user_info->certs_and_sign;
    owner_cert = (const vs_provision_cert_t *)&add_user_info->certs_and_sign[add_user_info->current_owner_cert_sz];

    // Check owner
    STATUS_CHECK_RET(_verify_owner_cert(owner_cert), "Wrong owner");

    // Check a new user
    STATUS_CHECK_RET(vs_provision_verify_cert(new_user_cert), "Cannot verify a new user");
    if (VS_CODE_OK == vs_users_get_name((vs_user_type_t)add_user_info->user_type,
                                        (vs_pubkey_dated_t*)new_user_cert->raw_cert,
                                        found_name, USER_NAME_SZ_MAX)) {
        VS_LOG_WARNING("User already present: %s", (const char *)add_user_info->new_user_name);
        return VS_CODE_ERR_USER_PRESENT;
    }

    // Calculate hash of stuff under signature
    vs_sign_t *sign;
    vs_pubkey_dated_t *dated_key;
    uint8_t *raw_pubkey;
    int hash_size;

    ???

    hash_size = vs_secmodule_get_hash_len(sign->hash_type);
    CHECK_RET(hash_size > 0, VS_CODE_ERR_CRYPTO, "Unsupported hash type");
    uint8_t hash[hash_size];
    size_t signed_data_sz = sizeof(vs_scrt_rusr_request_t) + cert_sz;
    uint16_t res_sz;
    STATUS_CHECK_RET(_secmodule->hash(sign->hash_type, request, signed_data_sz, hash, hash_size, &res_sz),
                     "Error hash create");

    // Verify signature
    dated_key = (vs_pubkey_dated_t *)current_owner_cert->raw_cert;
    raw_pubkey = &dated_key->pubkey.meta_and_pubkey[dated_key->pubkey.meta_data_sz];
    STATUS_CHECK_RET(_secmodule->ecdsa_verify(sign->ec_type,
                                              raw_pubkey,
                                              vs_secmodule_get_pubkey_len(dated_key->pubkey.ec_type),
                                              sign->hash_type,
                                              hash,
                                              sign->raw_sign_pubkey,
                                              vs_secmodule_get_signature_len(sign->ec_type)),
                     "Signature is wrong");

    // Add a new user
    STATUS_CHECK_RET(vs_users_add((vs_user_type_t)add_user_info->user_type,
                                  (const char *)add_user_info->new_user_name,
                                  (vs_pubkey_dated_t*)new_user_cert->raw_cert),
                     "Cannot add a new user");

    return VS_CODE_OK;
}

/******************************************************************/
static vs_status_e
_scrt_remove_user_request_processor(const uint8_t *request,
                                    const uint16_t request_sz,
                                    uint8_t *response,
                                    const uint16_t response_buf_sz,
                                    uint16_t *response_sz) {
    vs_status_e ret_code;
    const vs_scrt_rusr_request_t *remove_user_info = (const vs_scrt_rusr_request_t *)request;
    size_t rm_user_name_sz;
    vs_provision_cert_t *current_owner_cert;
    uint16_t cert_sz;

    // Check input parameters
    CHECK_NOT_ZERO_RET(request, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_RET(request_sz > sizeof(vs_scrt_rusr_request_t),
              VS_CODE_ERR_INCORRECT_ARGUMENT,
              "Unsupported request structure vs_scrt_rusr_request_t");
    CHECK_NOT_ZERO_RET(remove_user_info->user_type < VS_USER_TYPE_MAX, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_NOT_ZERO_RET(remove_user_info->rm_user_name[0], VS_CODE_ERR_INCORRECT_ARGUMENT);
    rm_user_name_sz = strnlen((const char *)remove_user_info->rm_user_name, USER_NAME_SZ_MAX);
    CHECK_NOT_ZERO_RET(rm_user_name_sz < USER_NAME_SZ_MAX, VS_CODE_ERR_INCORRECT_ARGUMENT);

    // Check owner
    current_owner_cert = (vs_provision_cert_t*)remove_user_info->current_owner_cert_and_sign;
    STATUS_CHECK_RET(_verify_owner_cert(current_owner_cert), "Wrong owner");

    // Check data signature
    vs_sign_t *sign;
    vs_pubkey_dated_t *dated_key;
    uint8_t *raw_pubkey;
    int hash_size;
    STATUS_CHECK_RET(vs_provision_cert_size(current_owner_cert, &cert_sz), "Cannot get certificate size");
    sign = (vs_sign_t *)&remove_user_info->current_owner_cert_and_sign[cert_sz];

    // Calculate hash of stuff under signature
    hash_size = vs_secmodule_get_hash_len(sign->hash_type);
    CHECK_RET(hash_size > 0, VS_CODE_ERR_CRYPTO, "Unsupported hash type");
    uint8_t hash[hash_size];
    size_t signed_data_sz = sizeof(vs_scrt_rusr_request_t) + cert_sz;
    uint16_t res_sz;
    STATUS_CHECK_RET(_secmodule->hash(sign->hash_type, request, signed_data_sz, hash, hash_size, &res_sz),
                     "Error hash create");

    // Verify signature
    dated_key = (vs_pubkey_dated_t *)current_owner_cert->raw_cert;
    raw_pubkey = &dated_key->pubkey.meta_and_pubkey[dated_key->pubkey.meta_data_sz];
    STATUS_CHECK_RET(_secmodule->ecdsa_verify(sign->ec_type,
                                              raw_pubkey,
                                              vs_secmodule_get_pubkey_len(dated_key->pubkey.ec_type),
                                              sign->hash_type,
                                              hash,
                                              sign->raw_sign_pubkey,
                                              vs_secmodule_get_signature_len(sign->ec_type)),
                     "Signature is wrong");

    // Remove user
    STATUS_CHECK_RET(vs_users_remove_by_name((vs_user_type_t)remove_user_info->user_type,
                                             (const char *)remove_user_info->rm_user_name),
                     "Cannot remove user");

    return VS_CODE_OK;
}

/******************************************************************/
static vs_status_e
_scrt_get_users_request_processor(const uint8_t *request,
                                  const uint16_t request_sz,
                                  uint8_t *response,
                                  const uint16_t response_buf_sz,
                                  uint16_t *response_sz) {
    vs_status_e ret_code;
    int i;
    vs_scrt_gusr_tiny_t *tiny_info;
    uint8_t read_key[USER_KEY_BUF_SZ_MAX];
    uint16_t key_sz;
    vs_pubkey_dated_t *read_key_dated = (vs_pubkey_dated_t *)read_key;
    const vs_scrt_gusr_request_t *get_users_request = (const vs_scrt_gusr_request_t *)request;
    vs_scrt_gusr_response_t *get_users_response = (vs_scrt_gusr_response_t *)response;

    // Check input parameters
    CHECK_NOT_ZERO_RET(request, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_RET(request_sz > sizeof(vs_scrt_gusr_request_t),
              VS_CODE_ERR_INCORRECT_ARGUMENT,
              "Unsupported request structure vs_scrt_gusr_request_t");
    CHECK_NOT_ZERO_RET(get_users_request->user_type < VS_USER_TYPE_MAX, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_NOT_ZERO_RET(response, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_NOT_ZERO_RET(response_sz, VS_CODE_ERR_INCORRECT_ARGUMENT);
    CHECK_RET(response_buf_sz > (sizeof(vs_scrt_gusr_response_t)
                                 + get_users_response->users_in_resp * sizeof(vs_scrt_gusr_tiny_t)),
              VS_CODE_ERR_INCORRECT_ARGUMENT,
              "Unsupported request structure vs_scrt_gusr_response_t");

    // Fill response
    get_users_response->user_type = get_users_request->user_type;
    get_users_response->users_offset = get_users_request->users_offset;
    get_users_response->users_in_resp = 0;

    tiny_info = (vs_scrt_gusr_tiny_t *)get_users_response->users;
    for (i = 0; i < get_users_request->max_users_per_resp; i++) {
        ret_code = vs_users_get_by_num((vs_user_type_t)get_users_request->user_type,
                                       get_users_request->users_offset + i,
                                       (char *)tiny_info->user_name, USER_NAME_SZ_MAX,
                                       read_key_dated, USER_KEY_BUF_SZ_MAX, &key_sz);

        if (VS_CODE_ERR_USER_NOT_FOUND == ret_code) {
            VS_LOG_DEBUG("No more users to load");
            return VS_CODE_OK;
        }

        if (VS_CODE_OK != ret_code) {
            VS_LOG_ERROR("Cannot load user info");
            return ret_code;
        }

        key_sz -= sizeof(vs_pubkey_dated_t) - sizeof(vs_pubkey_t);
        VS_IOT_MEMCPY(&tiny_info->user_pub_key,
                      &read_key_dated->pubkey,
                      key_sz);

        ++get_users_response->users_in_resp;

        tiny_info = (vs_scrt_gusr_tiny_t *)((uint8_t *)tiny_info + USER_NAME_SZ_MAX + key_sz);
    }

    return VS_CODE_OK;
}

/******************************************************************************/
static vs_status_e
_scrt_request_processor(const struct vs_netif_t *netif,
                        const vs_ethernet_header_t *eth_header,
                        vs_snap_element_t element_id,
                        const uint8_t *request,
                        const uint16_t request_sz,
                        uint8_t *response,
                        const uint16_t response_buf_sz,
                        uint16_t *response_sz) {
    (void)netif;

    *response_sz = 0;

    switch (element_id) {
    case VS_SCRT_INFO:
        return _scrt_info_request_processor(request, request_sz, response, response_buf_sz, response_sz);

    case VS_SCRT_GSEK:
        return _scrt_get_session_key_request_processor(request, request_sz, response, response_buf_sz, response_sz);

    case VS_SCRT_AUSR:
        return _scrt_add_user_request_processor(request, request_sz, response, response_buf_sz, response_sz);

    case VS_SCRT_RUSR:
        return _scrt_remove_user_request_processor(request, request_sz, response, response_buf_sz, response_sz);

    case VS_SCRT_GUSR:
        return _scrt_get_users_request_processor(request, request_sz, response, response_buf_sz, response_sz);

    default:
        VS_LOG_ERROR("Unsupported _CFG command");
        VS_IOT_ASSERT(false);
        return VS_CODE_COMMAND_NO_RESPONSE;
    }
}

/******************************************************************************/
const vs_snap_service_t *
vs_snap_scrt_server(vs_secmodule_impl_t *secmodule, vs_snap_scrt_server_service_t impl) {
    static vs_snap_service_t _scrt;

    CHECK_NOT_ZERO_RET(secmodule, NULL);

    if (!_scrt_service_ready) {
        _scrt_service_ready = true;
        _secmodule = secmodule;

        _scrt.user_data = NULL;
        _scrt.id = VS_SCRT_SERVICE_ID;
        _scrt.request_process = _scrt_request_processor;
        _scrt.response_process = NULL;
        _scrt.periodical_process = NULL;

        // Save callbacks
        VS_IOT_MEMCPY(&_impl, &impl, sizeof(impl));
    }

    return &_scrt;
}

/******************************************************************************/

#endif // SCRT_SERVER