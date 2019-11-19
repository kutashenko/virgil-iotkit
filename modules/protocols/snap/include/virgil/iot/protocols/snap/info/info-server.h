//  Copyright (C) 2015-2019 Virgil Security, Inc.
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

/*! \file info-server.h
 * \brief INFO for server
 */
// TODO : examples!

#ifndef VS_SECURITY_SDK_SNAP_SERVICES_INFO_SERVER_H
#define VS_SECURITY_SDK_SNAP_SERVICES_INFO_SERVER_H

#if INFO_SERVER

#ifdef __cplusplus
extern "C" {
#endif

#include <virgil/iot/protocols/snap/snap-structs.h>
#include <virgil/iot/firmware/firmware.h>
#include "info-structs.h"

// TODO : description???
/** Start notification
 *
 * Sends notification with device information.
 *
 * \param[in] device #vs_snap_info_device_t device information.
 *
 * \return #VS_CODE_OK in case of success or error code.
 */
typedef vs_status_e (*vs_snap_info_start_notif_srv_cb_t)(vs_snap_info_device_t *device);

/** INFO Server SNAP Service implementation
 *
 * This call returns INFO server implementation. It must be called before any INFO call.
 *
 * \param[in] tl_ctx Trust List storage context. Must not be NULL.
 * \param[in] fw_ctx Firmware storage context. Must not be NULL.
 * \param[in] startup_cb Startup notification server callback. If NULL, it won't be used.
 *
 * \return #vs_snap_service_t SNAP service description. Use this pointer to call #vs_snap_register_service.
 */
const vs_snap_service_t *
vs_snap_info_server(vs_storage_op_ctx_t *tl_ctx,
                    vs_storage_op_ctx_t *fw_ctx,
                    vs_snap_info_start_notif_srv_cb_t startup_cb);

/** INFO Server startup notification
 *
 * Sends startup notification.
 *
 * \param[in] netif SNAP service descriptor. Must not be NULL.
 *
 * \return #vs_snap_service_t SNAP service description. Use this pointer to call #vs_snap_register_service.
 */
vs_status_e
vs_snap_info_start_notification(const vs_netif_t *netif);

#ifdef __cplusplus
}
#endif

#endif // INFO_SERVER

#endif // VS_SECURITY_SDK_SNAP_SERVICES_INFO_SERVER_H