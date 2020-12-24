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

#if SCRT_CLIENT

#include <virgil/iot/protocols/snap/generated/snap_cvt.h>
#include <private/snap-private.h>
#include <virgil/iot/protocols/snap/scrt/scrt-client.h>
#include <virgil/iot/protocols/snap/scrt/scrt-structs.h>
#include <virgil/iot/protocols/snap/scrt/scrt-private.h>
#include <virgil/iot/macros/macros.h>
#include <virgil/iot/protocols/snap.h>
#include <virgil/iot/logger/logger.h>
#include <stdlib-config.h>
#include <global-hal.h>
#include <stdbool.h>
#include <string.h>

static vs_snap_service_t _scrt_client = {0};
static vs_snap_scrt_client_service_t _scrt_impl = {};

/******************************************************************************/
vs_status_e
vs_snap_scrt_get_info(const vs_netif_t *netif, const vs_mac_addr_t *mac) {
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
vs_status_e
vs_snap_scrt_request_session_key(const vs_netif_t *netif, const vs_mac_addr_t *mac) {
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
vs_status_e
vs_snap_scrt_add_user(const vs_netif_t *netif,
                      const vs_mac_addr_t *mac,
                      vs_user_type_t user_type,
                      const char *user_name) {
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
vs_status_e
vs_snap_scrt_remove_user(const vs_netif_t *netif,
                         const vs_mac_addr_t *mac,
                         vs_user_type_t user_type,
                         const char *user_name) {
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
vs_status_e
vs_snap_scrt_get_users(const vs_netif_t *netif,
                       const vs_mac_addr_t *mac,
                       vs_user_type_t user_type,
                       uint8_t offset,
                       uint8_t max_amount) {
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************************/
static vs_status_e
_scrt_service_response_processor(const struct vs_netif_t *netif,
                                 const vs_ethernet_header_t *eth_header,
                                 vs_snap_element_t element_id,
                                 bool is_ack,
                                 const uint8_t *response,
                                 const uint16_t response_sz) {
    vs_snap_transaction_id_t id = 0;
    vs_status_e res = is_ack ? VS_CODE_OK : VS_CODE_ERR_SNAP_UNKNOWN;

    switch (element_id) {

    case VS_SCRT_INFO:
        if (_scrt_impl.scrt_client_info_cb) {
            _scrt_impl.scrt_client_info_cb(id, res);
        }
        break;

    case VS_SCRT_GSEK:
        if (_scrt_impl.scrt_client_session_key_cb) {
            _scrt_impl.scrt_client_session_key_cb(id, res);
        }
        break;

    case VS_SCRT_AUSR:
        if (_scrt_impl.scrt_client_add_user_cb) {
            _scrt_impl.scrt_client_add_user_cb(id, res);
        }
        break;

    case VS_SCRT_RUSR:
        if (_scrt_impl.scrt_client_remove_user_cb) {
            _scrt_impl.scrt_client_remove_user_cb(id, res);
        }
        break;

    case VS_SCRT_GUSR:
        if (_scrt_impl.scrt_client_get_users_cb) {
            _scrt_impl.scrt_client_get_users_cb(id, res);
        }
        break;

    default: {}
    }

    return VS_CODE_OK;
}

/******************************************************************************/
const vs_snap_service_t *
vs_snap_scrt_client(vs_snap_scrt_client_service_t impl) {
    _scrt_client.user_data = 0;
    _scrt_client.id = VS_SCRT_SERVICE_ID;
    _scrt_client.request_process = NULL;
    _scrt_client.response_process = _scrt_service_response_processor;
    _scrt_client.periodical_process = NULL;

    return &_scrt_client;
}

/******************************************************************************/

#endif // SCRT_CLIENT
