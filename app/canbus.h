#ifndef CANBUS_H
#define CANBUS_H

#include <memory>

#include <QCanBus>
#include <QCanBusFrame>
#include <QCanBusDevice>
#include <QTimer>

class Canbus : public QObject
{
    Q_OBJECT
public:
    Canbus(QObject *parent = nullptr);

public slots:
    void receiveCanFrames();

signals:
    void newFrame(QString view);
    void newCanFrame(QCanBusFrame frame);
    /**
     * @brief Signals that no CAN frames have been received since defined timeout.
     */
    void timeout();
    /**
     * @brief Signals that timeout did occur because of the inactiveness of CAN bus but now a CAN frame has been received. Restarts the timeout calculation.
     */
    void timeoutCanceled();

private:
    std::unique_ptr<QCanBusDevice> canDevice_;
    QTimer timeout_;
};

#endif // CANBUS_H
