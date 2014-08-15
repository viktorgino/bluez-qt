#ifndef QBLUEZ_DEVICE_P_H
#define QBLUEZ_DEVICE_P_H

#include <QObject>
#include <QStringList>

#include "bluezdevice1.h"
#include "dbusproperties.h"

namespace QBluez
{

typedef org::bluez::Device1 BluezDevice;
typedef org::freedesktop::DBus::Properties DBusProperties;

class Device;
class Adapter;

class DevicePrivate : public QObject
{
public:
    explicit DevicePrivate(const QString &path, const QVariantMap &properties, Adapter *adapter, Device *parent);

    void init(const QVariantMap &properties);

    QDBusPendingReply<> setDBusProperty(const QString &name, const QVariant &value);
    void propertiesChanged(const QString &interface, const QVariantMap &changed, const QStringList &invalidated);
    void namePropertyChanged(const QString &value);
    void aliasPropertyChanged(const QString &value);
    void classPropertyChanged(quint32 value);
    void uuidsPropertyChanged(const QStringList &value);

    Device *q;
    BluezDevice *m_bluezDevice;
    DBusProperties *m_dbusProperties;

    QString m_address;
    QString m_name;
    QString m_alias;
    quint32 m_deviceClass;
    quint16 m_appearance;
    QString m_icon;
    bool m_paired;
    bool m_trusted;
    bool m_blocked;
    bool m_legacyPairing;
    qint16 m_rssi;
    bool m_connected;
    QStringList m_uuids;
    QString m_modalias;
    Adapter *m_adapter;
};

} // namespace QBluez

#endif // QBLUEZ_DEVICE_P_H
