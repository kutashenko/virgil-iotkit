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

#include <virgil/iot/qt/VSQIoTKit.h>

#include <cstdio>
#include <cstring>

using namespace VirgilIoTKit;

VSQSnapLampClient::VSQSnapCfgClient() {
    vs_snap_cfg_client_service_t impl;
    memset(&impl, 0, sizeof(impl));
    impl.client_wifi_config_cb = &VSQSnapCfgClient::onConfigResult;
    m_snapService = vs_snap_cfg_client(impl);
}

vs_status_e
VSQSnapCfgClient::onConfigResult(vs_snap_transaction_id_t id, vs_status_e res) {
    Q_UNUSED(id)
    if (VS_CODE_OK == res) {
        emit VSQSnapCfgClient::instance().fireConfigurationDone();
    } else {
        emit VSQSnapCfgClient::instance().fireConfigurationError();
    }

    return VS_CODE_OK;
}

void
VSQSnapCfgClient::onConfigureDevices() {
    qDebug() << "Configure ssid:<" << m_ssid << "> pass:<" << m_pass << ">";

    if (m_ssid.length() >= VS_CFG_STR_MAX) {
        VS_LOG_ERROR("SSID string is longer than %d", VS_CFG_STR_MAX);
    }

    if (m_pass.length() >= VS_CFG_STR_MAX) {
        VS_LOG_ERROR("Password string is longer than %d", VS_CFG_STR_MAX);
    }

    vs_cfg_wifi_configuration_t config;
    memset(&config, 0, sizeof(config));
    ::strcpy(reinterpret_cast<char *>(config.ssid), m_ssid.toStdString().c_str());
    ::strcpy(reinterpret_cast<char *>(config.pass), m_pass.toStdString().c_str());
    if (VS_CODE_OK != vs_snap_cfg_wifi_configure_device(vs_snap_netif_routing(),
                                 vs_snap_broadcast_mac(),
                                 &config)) {
        VS_LOG_ERROR("Cannot configure device");
    }
}

void
VSQSnapCfgClient::onSetConfigData(QString ssid, QString pass) {
    m_ssid = ssid;
    m_pass = pass;
}
