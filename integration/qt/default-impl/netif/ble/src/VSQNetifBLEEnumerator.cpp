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

#include <virgil/iot/qt/netif/VSQNetifBLEEnumerator.h>

/******************************************************************************/
void
VSQNetifBLEEnumerator::onDeviceDiscovered(const QBluetoothDeviceInfo &deviceInfo) {
    if (deviceInfo.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration &&
        !deviceInfo.name().isEmpty()) {

        qDebug() << "[VIRGIL] Device Discovered : " << deviceInfo.name() << " : " << deviceInfo.deviceUuid();
        const bool _isInsert = !m_devices.keys().contains(deviceInfo.name()) /*&& m_devices.count()*/;

        if (_isInsert) {
            // TODO: Fix it
            auto tmp = m_devices;
            tmp[deviceInfo.name()] = BLEDevInfo();
            const int _pos = tmp.keys().indexOf(deviceInfo.name());
            beginInsertRows(QModelIndex(), _pos, _pos);
            m_devices[deviceInfo.name()] = BLEDevInfo(deviceInfo, QDateTime::currentDateTime());
            endInsertRows();
        } else {
            m_devices[deviceInfo.name()] = BLEDevInfo(deviceInfo, QDateTime::currentDateTime());
        }

        const int _pos = m_devices.keys().indexOf(deviceInfo.name());

        qDebug() << "Updated data: " << _pos;
        const auto _idx = createIndex(_pos, 0);
        emit dataChanged(_idx, _idx);
    }
}

/******************************************************************************/
void
VSQNetifBLEEnumerator::cleanOldDevices() {
    for (const auto &k: m_devices.keys()) {
        if (m_devices[k].lastUpdate.msecsTo(QDateTime::currentDateTime()) > kInactiveTimeoutMS) {
            const auto _pos = m_devices.keys().indexOf(k);
            beginRemoveRows(QModelIndex(), _pos, _pos);
            m_devices.remove(k);
            endRemoveRows();
        }
    }
}

/******************************************************************************/
void
VSQNetifBLEEnumerator::onDiscoveryFinished() {
    if (!QObject::sender())
        return;
    QObject::sender()->deleteLater();
    emit fireDiscoveryFinished();

    QTimer::singleShot(500, [this]() {
        startDiscovery();
    } );
}

/******************************************************************************/
void
VSQNetifBLEEnumerator::select(QString devName) const {
    if (m_devices.keys().contains(devName)) {
        emit fireDeviceSelected(m_devices[devName].info);
    }
}

/******************************************************************************/
void
VSQNetifBLEEnumerator::startDiscovery() {
    cleanOldDevices();

    // Create a discovery agent and connect to its signals
    QBluetoothDeviceDiscoveryAgent *discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    discoveryAgent->setLowEnergyDiscoveryTimeout(kBLEDiscoverPeriodMS);

    discoveryAgent->setInquiryType(QBluetoothDeviceDiscoveryAgent::LimitedInquiry);
    connect(discoveryAgent,
            &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this,
            &VSQNetifBLEEnumerator::onDeviceDiscovered);

    connect(discoveryAgent,
            &QBluetoothDeviceDiscoveryAgent::finished,
            this,
            &VSQNetifBLEEnumerator::onDiscoveryFinished);

    connect(discoveryAgent,
            &QBluetoothDeviceDiscoveryAgent::canceled,
            this,
            &VSQNetifBLEEnumerator::onDiscoveryFinished);

    connect(discoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)), this, SLOT(onDiscoveryFinished()));

    discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
}

/******************************************************************************/
int
VSQNetifBLEEnumerator::rowCount(const QModelIndex &parent) const {
    return m_devices.count();
}

/******************************************************************************/
int
VSQNetifBLEEnumerator::columnCount(const QModelIndex &parent) const {
    return 1;
}

/******************************************************************************/
QVariant
VSQNetifBLEEnumerator::data(const QModelIndex &index, int role) const {
    qDebug() << "Requested index: " << index.column() << " x " << index.row() << " x " << role;
    if (index.row() < m_devices.count()) {
        auto key = m_devices.keys().at(index.row());

        switch(role) {
        case Element::Name:
            return m_devices[key].info.name();

        case Element::Manufacture:
            return "";

        case Element::RSSI:
            return m_devices[key].info.rssi();

        case Element::Initialized:
            return index.row() % 2;

        }
    }

    return QVariant();
}

/******************************************************************************/
QHash<int, QByteArray>
VSQNetifBLEEnumerator::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[Name] = "name";
    roles[Manufacture] = "manufacture";
    roles[RSSI] = "rssi";
    roles[Initialized] = "initialized";
    return roles;
}

/******************************************************************************/
