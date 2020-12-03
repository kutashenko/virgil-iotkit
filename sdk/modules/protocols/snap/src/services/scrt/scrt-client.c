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
// static vs_snap_scrt_client_service_t _scrt_impl = {};

/******************************************************************************/
static vs_status_e
_scrt_service_response_processor(const struct vs_netif_t *netif,
                                 const vs_ethernet_header_t *eth_header,
                                 vs_snap_element_t element_id,
                                 bool is_ack,
                                 const uint8_t *response,
                                 const uint16_t response_sz) {

    return VS_CODE_ERR_NOT_IMPLEMENTED;
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
