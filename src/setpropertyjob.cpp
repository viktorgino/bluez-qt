#include "setpropertyjob.h"
#include "adapter_p.h"
#include "device_p.h"

#include <QDBusPendingReply>
#include <QDBusPendingCallWatcher>

namespace QBluez
{

class SetPropertyJobPrivate : public QObject
{
    Q_OBJECT

public:
    SetPropertyJobPrivate(SetPropertyJob *q, const QString &name, const QVariant &value);

    void doStart();

    SetPropertyJob *q;
    QString m_name;
    QVariant m_value;
};

SetPropertyJobPrivate::SetPropertyJobPrivate(SetPropertyJob *q, const QString &name, const QVariant &value)
    : QObject(q)
    , q(q)
    , m_name(name)
    , m_value(value)
{
}

void SetPropertyJobPrivate::doStart()
{
    QDBusPendingReply<> call;

    if (AdapterPrivate *adapter = qobject_cast<AdapterPrivate *>(q->parent())) {
        call = adapter->setDBusProperty(m_name, m_value);
    } else if (DevicePrivate *device = qobject_cast<DevicePrivate *>(q->parent())) {
        call = device->setDBusProperty(m_name, m_value);
    } else {
        qFatal("SetPropertyJob must be parented to AdapterPrivate or DevicePrivate!");
    }

    QDBusPendingCallWatcher *watcher = new QDBusPendingCallWatcher(call, this);

    connect(watcher, &QDBusPendingCallWatcher::finished, [ this, watcher ]() {
        const QDBusPendingReply<> &reply = *watcher;
        watcher->deleteLater();
        if (reply.isError()) {
            q->setError(SetPropertyJob::UserDefinedError);
            q->setErrorText(reply.error().message());
        }
        q->emitResult();
    });
}

SetPropertyJob::SetPropertyJob(const QString &name, const QVariant &value, QObject *parent)
    : Job(parent)
    , d(new SetPropertyJobPrivate(this, name, value))
{
}

SetPropertyJob::~SetPropertyJob()
{
    delete d;
}

void SetPropertyJob::doStart()
{
    d->doStart();
}

void SetPropertyJob::doEmitResult()
{
    Q_EMIT result(this);
}

} // namespace QBluez

#include "setpropertyjob.moc"
