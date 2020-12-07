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

#ifndef _VIRGIL_IOTKIT_QT_SNAP_CFG_CLIENT_SERVICE_H_
#define _VIRGIL_IOTKIT_QT_SNAP_CFG_CLIENT_SERVICE_H_

#include <QtCore>

#include <virgil/iot/protocols/snap/cfg/cfg-structs.h>
#include <virgil/iot/protocols/snap/cfg/cfg-client.h>
#include <virgil/iot/qt/helpers/VSQSingleton.h>
#include <virgil/iot/qt/protocols/snap/VSQSnapServiceBase.h>

using namespace VirgilIoTKit;

class VSQSnapCfgClient final :
        public QObject,
        public VSQSingleton<VSQSnapCfgClient>,
        public VSQSnapServiceBase {

    Q_OBJECT

    friend VSQSingleton<VSQSnapCfgClient>;

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
        return VSQFeatures::SNAP_CFG_CLIENT;
    }

    /** Get service name
     *
     * \return Service name
     */
    const QString &
    serviceName() const override {
        static QString name{"_CFG Client"};
        return name;
    }

    Q_INVOKABLE void
    setNetifRestriction(QSharedPointer<VSQNetifBase> restriction) {
        m_defaultNetif = restriction;
    }

signals:
    void fireConfigurationDone();
    void fireConfigurationError();

public slots:
    void
    onConfigureDevices();

    Q_INVOKABLE void
    onSetConfigData(QString ssid, QString pass);

private:
    const VirgilIoTKit::vs_snap_service_t *m_snapService;

    VSQSnapCfgClient();
    virtual ~VSQSnapCfgClient() = default;

    static vs_status_e
    onConfigResult(vs_snap_transaction_id_t id, vs_status_e res);

    QString m_ssid;
    QString m_pass;

    QSharedPointer<VSQNetifBase> m_defaultNetif;
};

#endif // _VIRGIL_IOTKIT_QT_SNAP_CFG_CLIENT_SERVICE_H_
