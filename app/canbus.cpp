#include "canbus.h"

#include <iostream>
#include "configuration.h"

Canbus::Canbus(QObject *parent) : QObject(parent)
{
    QString errorString;
    canDevice_.reset(QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"), Configuration::getInstance()->CAN_BUS_NAME, &errorString));

    if(!canDevice_){
        throw std::runtime_error(errorString.toStdString());
    }

    if(!canDevice_->connectDevice()){
        throw std::runtime_error(errorString.toStdString());
    }

    connect(canDevice_.get(), &QCanBusDevice::framesReceived,
            this, &Canbus::receiveCanFrames);

    connect(&timeout_, &QTimer::timeout,
            this, &Canbus::timeout);
    timeout_.setSingleShot(true);
    timeout_.start(Configuration::getInstance()->CAN_BUS_TIMEOUT);

}

void Canbus::receiveCanFrames()
{
    if (!timeout_.isActive()) {
        emit timeoutCanceled();
    }
    timeout_.stop();
    while (canDevice_->framesAvailable()) {
        const QCanBusFrame frame = canDevice_->readFrame();

        QString view;
        if (frame.frameType() == QCanBusFrame::ErrorFrame)
            view = canDevice_->interpretErrorFrame(frame);
        else
            view = frame.toString();

        emit newFrame(view);
        emit newCanFrame(frame);
    }
    timeout_.start(Configuration::getInstance()->CAN_BUS_TIMEOUT);
}
