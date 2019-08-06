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

#ifndef VS_UPDATE_INTERFACE_H
#define VS_UPDATE_INTERFACE_H

int
vs_update_read_firmware_data_hal(uint8_t *manufacture_id,
                                 uint8_t *device_type,
                                 uint32_t offset,
                                 uint8_t *data,
                                 uint16_t buf_sz,
                                 uint16_t *read_sz);
int
vs_update_write_firmware_data_hal(uint8_t *manufacture_id,
                                  uint8_t *device_type,
                                  uint32_t offset,
                                  const void *data,
                                  uint16_t data_sz);
int
vs_update_remove_firmware_data_hal(uint8_t *manufacture_id, uint8_t *device_type);

int
vs_update_read_firmware_descriptor_table_hal(uint8_t *data, uint16_t buf_sz, uint16_t *read_sz);
int
vs_update_write_firmware_descriptor_table_hal(const void *data, uint16_t data_sz);
int
vs_update_remove_firmware_descriptor_table_hal(void);
int
vs_update_get_firmware_descriptor_table_len_hal(void);

int
vs_update_get_firmware_image_len_hal(uint8_t *manufacture_id, uint8_t *device_type);
#endif // VS_UPDATE_INTERFACE_H
