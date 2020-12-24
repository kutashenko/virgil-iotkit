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

// #define SCRT_SERVER 1

#if SCRT_SERVER

#include <virgil/iot/protocols/snap/scrt/scrt-server.h>
#include <virgil/iot/protocols/snap/scrt/scrt-private.h>
#include <virgil/iot/protocols/snap/scrt/scrt-structs.h>
#include <virgil/iot/protocols/snap/generated/snap_cvt.h>
#include <virgil/iot/protocols/snap.h>
#include <virgil/iot/status_code/status_code.h>
#include <virgil/iot/logger/logger.h>
#include <virgil/iot/macros/macros.h>
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
    STATUS_CHECK_RET(vs_provision_own_cert(&info_data->own_cert, cert_buf_sz), "Cannot load own certificate");

    *response_sz = sizeof(vs_scrt_info_response_t) + info_data->own_cert.key_sz + info_data->own_cert.signature_sz;

    return VS_CODE_OK;
}

/******************************************************************/
static vs_status_e
_scrt_get_session_key_request_processor(const uint8_t *request,
                                        const uint16_t request_sz,
                                        uint8_t *response,
                                        const uint16_t response_buf_sz,
                                        uint16_t *response_sz) {
    VS_LOG_DEBUG("SCRT::GSEK request");
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************/
static vs_status_e
_scrt_add_user_request_processor(const uint8_t *request,
                                 const uint16_t request_sz,
                                 uint8_t *response,
                                 const uint16_t response_buf_sz,
                                 uint16_t *response_sz) {
    VS_LOG_DEBUG("SCRT::AUSR request");
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************/
static vs_status_e
_scrt_remove_user_request_processor(const uint8_t *request,
                                    const uint16_t request_sz,
                                    uint8_t *response,
                                    const uint16_t response_buf_sz,
                                    uint16_t *response_sz) {
    VS_LOG_DEBUG("SCRT::RUSR request");
    return VS_CODE_ERR_NOT_IMPLEMENTED;
}

/******************************************************************/
static vs_status_e
_scrt_get_users_request_processor(const uint8_t *request,
                                  const uint16_t request_sz,
                                  uint8_t *response,
                                  const uint16_t response_buf_sz,
                                  uint16_t *response_sz) {
    VS_LOG_DEBUG("SCRT::GUSR request");
    return VS_CODE_ERR_NOT_IMPLEMENTED;
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