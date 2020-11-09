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


#ifndef YIOT_SNAP_SERVICES_LAMP_PRIVATE_H
#define YIOT_SNAP_SERVICES_LAMP_PRIVATE_H

#include <virgil/iot/protocols/snap/lamp/lamp-server.h>
#include <virgil/iot/protocols/snap/lamp/lamp-structs.h>
#include <virgil/iot/protocols/snap.h>
#include <virgil/iot/status_code/status_code.h>
#include <virgil/iot/protocols/snap/snap-structs.h>

// mute "error: multi-character character constant" message
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmultichar"
typedef enum { VS_LAMP_SERVICE_ID = HTONL_IN_COMPILE_TIME('LAMP') } vs_lamp_t;

typedef enum {
    VS_LAMP_GLST = HTONL_IN_COMPILE_TIME('GLST'), /* Get Lamp STate */
    VS_LAMP_SLST = HTONL_IN_COMPILE_TIME('SLST'), /* Set Lamp STate */
} vs_snap_lamp_element_e;
#pragma GCC diagnostic pop

#endif // YIOT_SNAP_SERVICES_LAMP_PRIVATE_H
