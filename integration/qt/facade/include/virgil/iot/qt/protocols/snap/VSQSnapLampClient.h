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

#ifndef _YIOT_QT_SNAP_LAMP_CLIENT_SERVICE_H_
#define _YIOT_QT_SNAP_LAMP_CLIENT_SERVICE_H_

#include <QtCore>

#include <virgil/iot/protocols/snap/cfg/cfg-structs.h>
#include <virgil/iot/protocols/snap/cfg/cfg-client.h>
#include <virgil/iot/qt/helpers/VSQSingleton.h>
#include <virgil/iot/qt/protocols/snap/VSQSnapServiceBase.h>

using namespace VirgilIoTKit;

class VSQSnapLampClient final :
        public QObject,
        public VSQSingleton<VSQSnapLampClient>,
        public VSQSnapServiceBase {

    Q_OBJECT

    friend VSQSingleton<VSQSnapLampClient>;

public:

    /** Get service interface
     *
     * \return Service interface
     */
    const VirgilIoTKit::vs_snap_service_t *
    serviceInterface() override {
        return m_snapService;
    }

    /** Get service feature
     *
     * \return Service feature
     */
    VSQFeatures::EFeature
    serviceFeature() const override {
        return VSQFeatures::SNAP_LAMP_CLIENT;
    }

    /** Get service name
     *
     * \return Service name
     */
    const QString &
    serviceName() const override {
        static QString name{"LAMP Client"};
        return name;
    }

signals:

public slots:

private:
    const VirgilIoTKit::vs_snap_service_t *m_snapService;

    VSQSnapLampClient();
    ~VSQSnapLampClient() = default;

};

#endif // _YIOT_QT_SNAP_LAMP_CLIENT_SERVICE_H_
