// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QCanBusDevice>
#include <QtEndian>

#include "can_bus_router.h"

class CanBusRouter::Impl : public QObject
{
    Q_OBJECT

public:
    enum class SourceAddress : quint32
    {
        Engine = 0x00U,
    };

    enum class Pgn : quint32
    {
        EEC1 = 0xf004U,
        CCVS1 = 0xfef1U,
    };

    Impl(QCanBusDevice *canBus);
    virtual ~Impl();

    SourceAddress sourceAddress(quint32 frameId) const;
    Pgn pgn(quint32 frameId) const;

    QCanBusDevice *m_canBus;

public slots:
    void onFramesReceived();

signals:
    void newEngineQuantities(const QList<Quantity> &quantityColl);
};

CanBusRouter::Impl::Impl(QCanBusDevice *canBus)
    : m_canBus{canBus}
{
    connect(m_canBus, &QCanBusDevice::framesReceived,
            this, &Impl::onFramesReceived);
    m_canBus->connectDevice();
}

CanBusRouter::Impl::~Impl()
{
    m_canBus->disconnectDevice();
}

CanBusRouter::Impl::SourceAddress CanBusRouter::Impl::sourceAddress(quint32 frameId) const
{
    return SourceAddress(frameId & 0xff);
}

CanBusRouter::Impl::Pgn CanBusRouter::Impl::pgn(quint32 frameId) const
{
    return Pgn((frameId & 0x00ffff00) >> 8);
}

void CanBusRouter::Impl::onFramesReceived()
{
    QList<Quantity> quantityColl;
    for (const auto &frame : m_canBus->readAllFrames())
    {
        if (sourceAddress(frame.frameId()) == Impl::SourceAddress::Engine)
        {
            switch (pgn(frame.frameId()))
            {
            case Pgn::EEC1:
            {
                auto payload = frame.payload();
                quantityColl.append(Quantity{Quantity::Id::EngineSpeed, payload.mid(3, 2)});
                break;
            }
            case Pgn::CCVS1:
            {
                auto payload = frame.payload();
                quantityColl.append(Quantity{Quantity::Id::VehicleSpeed, payload.mid(1, 2)});
                break;
            }
            default:
                break;
            }
        }
    }
    emit newEngineQuantities(quantityColl);
}


CanBusRouter::CanBusRouter(QCanBusDevice *canBus, QObject *parent)
    : QObject{parent}
    , m_impl{new Impl{canBus}}
{
    connect(m_impl.get(), &Impl::newEngineQuantities,
            this, &CanBusRouter::newEngineQuantities);
}

CanBusRouter::~CanBusRouter()
{
}

#include "can_bus_router.moc"
