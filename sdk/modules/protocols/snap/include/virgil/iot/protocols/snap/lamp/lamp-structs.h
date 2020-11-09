//
//                                  _____   _______
//                                 |_   _| |__   __|
//                                   | |  ___ | |
//                                   | | / _ \| |
//                                  _| || (_) | |
//                                 |_____\___/|_|
//
//    _  ________ ______ _____    _____ _______    _____ _____ __  __ _____  _      ______
//   | |/ /  ____|  ____|  __ \  |_   _|__   __|  / ____|_   _|  \/  |  __ \| |    |  ____|
//   | ' /| |__  | |__  | |__) |   | |    | |    | (___   | | | \  / | |__) | |    | |__
//   |  < |  __| |  __| |  ___/    | |    | |     \___ \  | | | |\/| |  ___/| |    |  __|
//   | . \| |____| |____| |       _| |_   | |     ____) |_| |_| |  | | |    | |____| |____
//   |_|\_\______|______|_|      |_____|  |_|    |_____/|_____|_|  |_|_|    |______|______|
//
//
//
//   09 October 2020
//   Lead Maintainer: Roman Kutashenko <kutashenko@gmail.com>

#ifndef YIOT_SNAP_SERVICES_LAMP_STRUCTS_H
#define YIOT_SNAP_SERVICES_LAMP_STRUCTS_H

#include <stdint.h>

#ifdef __cplusplus
namespace VirgilIoTKit {
extern "C" {
#endif

typedef struct __attribute__((__packed__)) {
    uint8_t is_rgb;
    uint16_t cct_min;
    uint16_t cct_max;
} vs_snap_lamp_capabilities_t;

typedef struct __attribute__((__packed__)) {
    uint8_t is_on;
    uint16_t brightness;
    uint16_t cct;
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    vs_snap_lamp_capabilities_t caps;
} vs_snap_lamp_state_t;

#ifdef __cplusplus
} // extern "C"
} // namespace VirgilIoTKit
#endif

#endif // YIOT_SNAP_SERVICES_LAMP_STRUCTS_H
