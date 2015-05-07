/*
 * BluezQt - Asynchronous Bluez wrapper library
 *
 * Copyright (C) 2014-2015 David Rosca <nowrep@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) version 3, or any
 * later version accepted by the membership of KDE e.V. (or its
 * successor approved by the membership of KDE e.V.), which shall
 * act as a proxy defined in Section 6 of version 3 of the license.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BLUEZQT_DEVICESMODEL_H
#define BLUEZQT_DEVICESMODEL_H

#include <QAbstractListModel>

#include "types.h"
#include "bluezqt_export.h"

namespace BluezQt
{

class Manager;
class Device;

/**
 * Model of all devices.
 *
 * This class represents a model of all devices.
 *
 * Example use in QML code:
 * @code
 * import org.kde.bluezqt 1.0 as BluezQt
 *
 * BluezQt.Manager {
 *     id: btManager;
 * }
 *
 * BluezQt.DevicesModel {
 *     manager: btManager
 * }
 * @endcode
 */
class BLUEZQT_EXPORT DevicesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    /**
     * Device data roles.
     */
    enum DeviceRoles {
        /** UBI of the device (QString) */
        UbiRole = Qt::UserRole + 100,
        /** Address of the device (QString) */
        AddressRole = Qt::UserRole + 101,
        /** Name of the device (QString) */
        NameRole = Qt::UserRole + 102,
        /** Friendly name of the device (QString) */
        FriendlyNameRole = Qt::UserRole + 103,
        /** Remote name of the device (QString) */
        RemoteNameRole = Qt::UserRole + 104,
        /** Class of the device (quint32) */
        ClassRole = Qt::UserRole + 105,
        /** Type of the device (DeviceType) */
        TypeRole = Qt::UserRole + 106,
        /** Appearance of the device (quint16) */
        AppearanceRole = Qt::UserRole + 107,
        /** Icon name of the device (QString) */
        IconRole = Qt::UserRole + 108,
        /** Indicates whether the device is paired (bool) */
        PairedRole = Qt::UserRole + 109,
        /** Indicates whether the device is trusted (bool) */
        TrustedRole = Qt::UserRole + 110,
        /** Indicates whether the device is blocked (bool) */
        BlockedRole = Qt::UserRole + 111,
        /** Indicates whether the device has legacy pairing (bool) */
        LegacyPairingRole = Qt::UserRole + 112,
        /** Received Signal Strength Indicator of the device (qint16) */
        RssiRole = Qt::UserRole + 113,
        /** Indicates whether the device is connected (bool) */
        ConnectedRole = Qt::UserRole + 114,
        /** UUIDs of supported services by the device (QStringList) */
        UuidsRole = Qt::UserRole + 115,
        /** Modalias of the device (QString) */
        ModaliasRole = Qt::UserRole + 116,
        /** Name of the associated adapter (QString) */
        AdapterNameRole = Qt::UserRole + 117,
        /** Address of the associated adapter (QString) */
        AdapterAddressRole = Qt::UserRole + 118,
        /** Indicates whether the associated adapter is powered (bool) */
        AdapterPoweredRole = Qt::UserRole + 119,
        /** Indicates whether the associated adapter is discoverable (bool) */
        AdapterDiscoverableRole = Qt::UserRole + 120,
        /** Indicates whether the associated adapter is pairable (bool) */
        AdapterPairableRole = Qt::UserRole + 121,
        /** Indicates whether the associated adapter is discovering (bool) */
        AdapterDiscoveringRole = Qt::UserRole + 122,
        /** UUIDs of supported services by the associated adapter (QStringList) */
        AdapterUuidsRole = Qt::UserRole + 123,
        /** Last role used by DevicesModel */
        LastRole = Qt::UserRole + 124
    };

    /**
     * Creates a new DevicesModel object.
     *
     * @param manager manager to be used
     * @param parent
     */
    explicit DevicesModel(Manager *manager, QObject *parent = Q_NULLPTR);

    /**
      * Destroys a DevicesModel object.
      */
    ~DevicesModel();

    /**
      * Reimplemented from QAbstractListModel::roleNames()
      */
    QHash<int, QByteArray> roleNames() const Q_DECL_OVERRIDE;

    /**
      * Reimplemented from QAbstractListModel::rowCount()
      */
    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    /**
      * Reimplemented from QAbstractListModel::data()
      */
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;

    /**
      * Reimplemented from QAbstractListModel::index()
      */
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

    /**
     * Returns a device for specified index.
     *
     * @param index index in model
     * @return device object
     */
    DevicePtr device(const QModelIndex &index) const;

private:
    class DevicesModelPrivate *const d;

    friend class DevicesModelPrivate;
};

} // namespace BluezQt

#endif // BLUEZQT_DEVICESMODEL_H
