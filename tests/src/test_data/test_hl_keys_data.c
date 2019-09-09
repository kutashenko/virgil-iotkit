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
#include <stdint.h>
#include <stddef.h>

const unsigned char recovery1_pub[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x3a, 0x47,
                                       0x4f, 0x57, 0xc6, 0x6b, 0x7c, 0xa7, 0x53, 0xc1, 0x61, 0x7f, 0x8d, 0x13, 0x78,
                                       0xf9, 0x68, 0xe3, 0x22, 0xf1, 0x7d, 0x21, 0x34, 0x69, 0x4e, 0x06, 0x78, 0xec,
                                       0x29, 0x21, 0xd4, 0x1b, 0x12, 0x77, 0x62, 0x03, 0x7f, 0x53, 0x76, 0x56, 0x73,
                                       0x04, 0xb8, 0xaa, 0xbb, 0x91, 0x3e, 0xff, 0x99, 0x1f, 0xac, 0xcd, 0x38, 0xf3,
                                       0xcd, 0x00, 0x97, 0xf5, 0x90, 0x43, 0x4b, 0xb5, 0xce, 0xdc};
const size_t recovery1_pub_len = 75;

const unsigned char recovery2_pub[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0xed, 0x5f,
                                       0x80, 0xf6, 0x71, 0x0e, 0xa9, 0xae, 0xfa, 0x9d, 0x18, 0x67, 0xbd, 0x1a, 0xd6,
                                       0x43, 0x7f, 0xca, 0xc7, 0x3f, 0xcd, 0x62, 0xde, 0xa7, 0xf8, 0x0d, 0x85, 0x03,
                                       0x3c, 0xf6, 0x3d, 0x3c, 0xc3, 0x7c, 0x6d, 0x83, 0x22, 0x83, 0xa8, 0xbb, 0x76,
                                       0x95, 0x21, 0x4d, 0x5d, 0xf2, 0x68, 0x51, 0xaa, 0xd7, 0xcb, 0xc3, 0x3f, 0xae,
                                       0x37, 0x5e, 0x7b, 0x08, 0xee, 0x30, 0x82, 0x08, 0x2c, 0x41};
const size_t recovery2_pub_len = 75;

const unsigned char auth1_pub[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x04, 0x36, 0xdc, 0xb8, 0x8a, 0x73, 0x4d, 0xde,
        0x9b, 0x1c, 0x8c, 0xdd, 0x3b, 0xc0, 0xf3, 0x91, 0x48, 0xd7, 0x48, 0x20, 0x74, 0x0c, 0xfb, 0xa6, 0xfe, 0x07,
        0x29, 0xb5, 0x2f, 0xf9, 0xbd, 0x88, 0x6a, 0x12, 0xf3, 0x0f, 0x16, 0xdd, 0x8f, 0xc8, 0xb7, 0xb4, 0x35, 0x86,
        0x8e, 0xec, 0xb9, 0x33, 0x8d, 0xd0, 0x82, 0xb4, 0xb1, 0x82, 0x16, 0xbf, 0xf1, 0x0f, 0x19, 0x88, 0x3b, 0x40,
        0x2a, 0x64, 0x53, 0x00, 0x03, 0x00, 0xb1, 0x24, 0x23, 0xb7, 0xaf, 0x99, 0xc5, 0xa5, 0x83, 0x19, 0x77, 0xfe,
        0x12, 0x31, 0x4e, 0x96, 0x31, 0x96, 0xa4, 0x15, 0xc1, 0x17, 0xb3, 0x8f, 0x5f, 0x30, 0xff, 0x71, 0x8c, 0x9c,
        0xdb, 0x58, 0x81, 0x0a, 0x3e, 0x92, 0x95, 0x05, 0xba, 0x9c, 0xe4, 0xa9, 0x90, 0x45, 0x04, 0x7c, 0xd2, 0xaf,
        0x6e, 0xa5, 0x8c, 0x47, 0x89, 0x4b, 0xf0, 0x55, 0x93, 0xed, 0xc9, 0xe8, 0x1e, 0x3a, 0xd3, 0x75, 0x04, 0x3a,
        0x47, 0x4f, 0x57, 0xc6, 0x6b, 0x7c, 0xa7, 0x53, 0xc1, 0x61, 0x7f, 0x8d, 0x13, 0x78, 0xf9, 0x68, 0xe3, 0x22,
        0xf1, 0x7d, 0x21, 0x34, 0x69, 0x4e, 0x06, 0x78, 0xec, 0x29, 0x21, 0xd4, 0x1b, 0x12, 0x77, 0x62, 0x03, 0x7f,
        0x53, 0x76, 0x56, 0x73, 0x04, 0xb8, 0xaa, 0xbb, 0x91, 0x3e, 0xff, 0x99, 0x1f, 0xac, 0xcd, 0x38, 0xf3, 0xcd,
        0x00, 0x97, 0xf5, 0x90, 0x43, 0x4b, 0xb5, 0xce, 0xdc};
const size_t auth1_pub_len = 207;

const unsigned char auth2_pub[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x04, 0x3a, 0xed, 0xcd, 0xa9, 0x78, 0x16, 0x46,
        0x03, 0x61, 0xbf, 0x1f, 0xfa, 0x84, 0xfe, 0x4e, 0x7c, 0x50, 0xdd, 0x90, 0x6b, 0x53, 0x87, 0xf0, 0x5a, 0xe8,
        0xc4, 0x47, 0xb3, 0x7d, 0x3b, 0x4e, 0x94, 0xc6, 0x6b, 0xe1, 0xcb, 0xd0, 0x56, 0xce, 0x74, 0x72, 0xfb, 0x62,
        0x91, 0xc9, 0xba, 0xc1, 0x70, 0x8e, 0x85, 0xf2, 0xc5, 0x81, 0x6f, 0x04, 0xe7, 0x40, 0x70, 0x1f, 0xf6, 0xdc,
        0xfd, 0x89, 0xd6, 0x00, 0x03, 0x00, 0x2c, 0x26, 0xa5, 0x02, 0xab, 0x60, 0x4d, 0x95, 0x20, 0xcb, 0xca, 0xf4,
        0x1c, 0x02, 0xab, 0x2a, 0x31, 0x7e, 0xd8, 0xb1, 0x4a, 0xa5, 0x67, 0x28, 0xe6, 0xdc, 0x2c, 0xf5, 0xf3, 0xef,
        0x57, 0xfe, 0xf9, 0x73, 0x93, 0x8b, 0x78, 0xe2, 0xcd, 0x02, 0xc0, 0x38, 0x42, 0xbc, 0x53, 0x19, 0xfe, 0x26,
        0x2a, 0x8c, 0x45, 0xab, 0x12, 0x8e, 0xd5, 0x95, 0x38, 0x8b, 0xe9, 0xbe, 0x27, 0x22, 0x70, 0x20, 0x04, 0xed,
        0x5f, 0x80, 0xf6, 0x71, 0x0e, 0xa9, 0xae, 0xfa, 0x9d, 0x18, 0x67, 0xbd, 0x1a, 0xd6, 0x43, 0x7f, 0xca, 0xc7,
        0x3f, 0xcd, 0x62, 0xde, 0xa7, 0xf8, 0x0d, 0x85, 0x03, 0x3c, 0xf6, 0x3d, 0x3c, 0xc3, 0x7c, 0x6d, 0x83, 0x22,
        0x83, 0xa8, 0xbb, 0x76, 0x95, 0x21, 0x4d, 0x5d, 0xf2, 0x68, 0x51, 0xaa, 0xd7, 0xcb, 0xc3, 0x3f, 0xae, 0x37,
        0x5e, 0x7b, 0x08, 0xee, 0x30, 0x82, 0x08, 0x2c, 0x41};
const size_t auth2_pub_len = 207;

const unsigned char firmware1_pub[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x04, 0x69, 0xf7, 0x7b, 0x9e, 0x01, 0xb4, 0x6c,
        0x32, 0x87, 0x74, 0xef, 0x68, 0x42, 0x2a, 0x2b, 0xf7, 0x25, 0xe7, 0xca, 0xcd, 0xbb, 0x0a, 0x57, 0xb5, 0xb5,
        0xb3, 0xbf, 0xb9, 0x2c, 0xef, 0x50, 0xd6, 0xd0, 0x6a, 0x4d, 0x04, 0x64, 0x22, 0xd0, 0xa0, 0x0b, 0x5b, 0x3d,
        0xed, 0xb6, 0xaf, 0x31, 0x8b, 0x3c, 0x9e, 0xfc, 0x32, 0x00, 0xf1, 0xfe, 0x6f, 0x3b, 0x87, 0xf3, 0xd3, 0x50,
        0xbd, 0xb0, 0x38, 0x00, 0x03, 0x00, 0x26, 0x6c, 0xd8, 0xc1, 0xda, 0x17, 0xc2, 0x3c, 0xa6, 0xfb, 0x50, 0x01,
        0x24, 0xf4, 0x8d, 0xad, 0x27, 0xf5, 0xcf, 0x9f, 0x17, 0xde, 0x4a, 0xb0, 0x22, 0x21, 0xa7, 0x41, 0xeb, 0xbe,
        0x72, 0xfb, 0x55, 0xf5, 0x18, 0x2a, 0x33, 0xcf, 0x47, 0x19, 0xc6, 0xb7, 0x4b, 0x12, 0x97, 0xd9, 0xf2, 0x2c,
        0x24, 0x30, 0x0e, 0xf4, 0x9d, 0xe1, 0xe5, 0x45, 0x67, 0xa1, 0xa8, 0x0f, 0xf8, 0x6e, 0x2e, 0x72, 0x04, 0x3a,
        0x47, 0x4f, 0x57, 0xc6, 0x6b, 0x7c, 0xa7, 0x53, 0xc1, 0x61, 0x7f, 0x8d, 0x13, 0x78, 0xf9, 0x68, 0xe3, 0x22,
        0xf1, 0x7d, 0x21, 0x34, 0x69, 0x4e, 0x06, 0x78, 0xec, 0x29, 0x21, 0xd4, 0x1b, 0x12, 0x77, 0x62, 0x03, 0x7f,
        0x53, 0x76, 0x56, 0x73, 0x04, 0xb8, 0xaa, 0xbb, 0x91, 0x3e, 0xff, 0x99, 0x1f, 0xac, 0xcd, 0x38, 0xf3, 0xcd,
        0x00, 0x97, 0xf5, 0x90, 0x43, 0x4b, 0xb5, 0xce, 0xdc};
const size_t firmware1_pub_len = 207;

const unsigned char firmware2_pub[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x04, 0xfc, 0xf2, 0x74, 0x01, 0x17, 0x8b, 0x77,
        0xa0, 0x64, 0x48, 0x96, 0xff, 0xe6, 0xba, 0xb6, 0x38, 0x63, 0xdb, 0x9c, 0x6d, 0x36, 0xa4, 0x42, 0x16, 0xb8,
        0xf1, 0x1a, 0xf5, 0xb9, 0x03, 0x9c, 0x7c, 0x25, 0x03, 0x07, 0x71, 0xbd, 0xc9, 0x90, 0xc0, 0xa0, 0x48, 0xe0,
        0xcb, 0x6b, 0x75, 0xfa, 0x68, 0x60, 0x12, 0xde, 0x72, 0x72, 0x0a, 0x08, 0xe5, 0x20, 0xe7, 0x64, 0x1b, 0x6d,
        0x41, 0xae, 0x6f, 0x00, 0x03, 0x00, 0x9e, 0x90, 0xf3, 0x44, 0x94, 0x06, 0x83, 0x82, 0x1d, 0x07, 0x5e, 0x8c,
        0x7b, 0xa3, 0xcc, 0x2e, 0x04, 0x8c, 0xc6, 0xc4, 0x30, 0x86, 0x17, 0xfe, 0xd8, 0x23, 0x5e, 0xd6, 0x3a, 0x28,
        0xfe, 0x51, 0xe8, 0x79, 0x14, 0xe7, 0x79, 0xcb, 0x4a, 0x63, 0x6c, 0x9e, 0x35, 0x3f, 0x35, 0xa7, 0xc8, 0x49,
        0x1a, 0x48, 0x0d, 0x09, 0x52, 0x0c, 0xd4, 0xd2, 0xc5, 0xa1, 0x1e, 0x37, 0x15, 0x01, 0xa3, 0xca, 0x04, 0xed,
        0x5f, 0x80, 0xf6, 0x71, 0x0e, 0xa9, 0xae, 0xfa, 0x9d, 0x18, 0x67, 0xbd, 0x1a, 0xd6, 0x43, 0x7f, 0xca, 0xc7,
        0x3f, 0xcd, 0x62, 0xde, 0xa7, 0xf8, 0x0d, 0x85, 0x03, 0x3c, 0xf6, 0x3d, 0x3c, 0xc3, 0x7c, 0x6d, 0x83, 0x22,
        0x83, 0xa8, 0xbb, 0x76, 0x95, 0x21, 0x4d, 0x5d, 0xf2, 0x68, 0x51, 0xaa, 0xd7, 0xcb, 0xc3, 0x3f, 0xae, 0x37,
        0x5e, 0x7b, 0x08, 0xee, 0x30, 0x82, 0x08, 0x2c, 0x41};
const size_t firmware2_pub_len = 207;

const unsigned char tl_service1_pub[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x04, 0xfd, 0x03, 0x44, 0x59, 0x58, 0xd3, 0x4b,
        0x38, 0xa7, 0x6f, 0x20, 0xf6, 0x23, 0xac, 0xb8, 0xa9, 0x2e, 0xb8, 0x88, 0xbe, 0xef, 0x54, 0x71, 0x0f, 0x8a,
        0xc5, 0xba, 0x8f, 0x63, 0xa5, 0x18, 0x29, 0x9c, 0xe6, 0xd5, 0x6b, 0xbb, 0x13, 0x8c, 0xf9, 0x6b, 0xd2, 0x79,
        0x97, 0x40, 0x5f, 0x85, 0xa2, 0x67, 0x9d, 0x0b, 0x73, 0xb9, 0xec, 0xbe, 0xe2, 0xd2, 0x08, 0x08, 0xcf, 0x9e,
        0x0a, 0x32, 0x48, 0x00, 0x03, 0x00, 0xde, 0xeb, 0x8b, 0xb2, 0xae, 0xe2, 0xef, 0x15, 0x8b, 0x7a, 0x93, 0x2f,
        0xd2, 0xa2, 0xec, 0x4e, 0xca, 0xe9, 0xd4, 0x3d, 0x8d, 0x88, 0x2c, 0xc4, 0x58, 0xf0, 0xe6, 0x4c, 0x51, 0x27,
        0xd1, 0x65, 0xfc, 0xf5, 0x6a, 0xa0, 0xf4, 0x31, 0xd1, 0xc1, 0x62, 0x72, 0xb3, 0x85, 0xd0, 0xf8, 0xde, 0x0c,
        0x1c, 0xf2, 0xcd, 0x67, 0x39, 0xb7, 0xce, 0x9b, 0x85, 0x87, 0xb0, 0xbc, 0xfb, 0xa6, 0x82, 0x8f, 0x04, 0xed,
        0x5f, 0x80, 0xf6, 0x71, 0x0e, 0xa9, 0xae, 0xfa, 0x9d, 0x18, 0x67, 0xbd, 0x1a, 0xd6, 0x43, 0x7f, 0xca, 0xc7,
        0x3f, 0xcd, 0x62, 0xde, 0xa7, 0xf8, 0x0d, 0x85, 0x03, 0x3c, 0xf6, 0x3d, 0x3c, 0xc3, 0x7c, 0x6d, 0x83, 0x22,
        0x83, 0xa8, 0xbb, 0x76, 0x95, 0x21, 0x4d, 0x5d, 0xf2, 0x68, 0x51, 0xaa, 0xd7, 0xcb, 0xc3, 0x3f, 0xae, 0x37,
        0x5e, 0x7b, 0x08, 0xee, 0x30, 0x82, 0x08, 0x2c, 0x41};
const size_t tl_service1_pub_len = 207;

const unsigned char tl_service2_pub[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x04, 0x74, 0xcc, 0xce, 0x19, 0xda, 0x37, 0x5c,
        0xf8, 0x26, 0xeb, 0x7a, 0x11, 0xa1, 0x28, 0x8b, 0xb9, 0x16, 0x5f, 0x8b, 0x0f, 0xc4, 0x70, 0x35, 0x0a, 0x96,
        0x9b, 0xcb, 0x79, 0xc8, 0xc8, 0x4b, 0x0d, 0x07, 0xdf, 0xed, 0xf1, 0x18, 0x61, 0x4c, 0xb3, 0x89, 0x22, 0xb0,
        0xd6, 0x1f, 0x7c, 0xdc, 0x86, 0x90, 0x28, 0x67, 0x64, 0xb3, 0xf4, 0xf2, 0xff, 0x23, 0x2c, 0x46, 0x9e, 0x28,
        0xbb, 0x11, 0xe3, 0x00, 0x03, 0x00, 0x90, 0xcf, 0xf7, 0x4b, 0xa5, 0x26, 0x8a, 0xc5, 0x62, 0x61, 0xad, 0x96,
        0x50, 0x11, 0xb3, 0x0d, 0x4f, 0xa2, 0xf4, 0x0c, 0xa1, 0x97, 0xc1, 0xbb, 0x48, 0x78, 0xfa, 0xcd, 0x94, 0x16,
        0x38, 0x9c, 0xc7, 0x96, 0x6a, 0x97, 0x29, 0xe0, 0x47, 0xd2, 0xb6, 0x0f, 0xca, 0x64, 0xec, 0xe5, 0xc3, 0x88,
        0xc1, 0xeb, 0x4b, 0x57, 0x28, 0x92, 0x0b, 0x32, 0xa5, 0xbd, 0xa9, 0x09, 0xfb, 0x3c, 0x30, 0x90, 0x04, 0x3a,
        0x47, 0x4f, 0x57, 0xc6, 0x6b, 0x7c, 0xa7, 0x53, 0xc1, 0x61, 0x7f, 0x8d, 0x13, 0x78, 0xf9, 0x68, 0xe3, 0x22,
        0xf1, 0x7d, 0x21, 0x34, 0x69, 0x4e, 0x06, 0x78, 0xec, 0x29, 0x21, 0xd4, 0x1b, 0x12, 0x77, 0x62, 0x03, 0x7f,
        0x53, 0x76, 0x56, 0x73, 0x04, 0xb8, 0xaa, 0xbb, 0x91, 0x3e, 0xff, 0x99, 0x1f, 0xac, 0xcd, 0x38, 0xf3, 0xcd,
        0x00, 0x97, 0xf5, 0x90, 0x43, 0x4b, 0xb5, 0xce, 0xdc};
const size_t tl_service2_pub_len = 207;

