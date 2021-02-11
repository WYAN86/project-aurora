#ifndef CANFRAMEHANDLER_H
#define CANFRAMEHANDLER_H

#include <QObject>
#include <QCanBusFrame>

#include "canmessages.h"
#include "cansignalbuffer.h"

class CanFrameHandler : public QObject
{
    Q_OBJECT
public:
    CanFrameHandler(QObject *parent = nullptr);

public slots:
    void handleFrame(QCanBusFrame frame);

signals:
    void newBMS_INFO1Message(BMS_INFO1 message);
    void newIC_Ctrl1Message(IC_Ctrl1 message);
    void newIC_Ctrl2Message(IC_Ctrl2 message);
    void newIC_Ctrl3Message(IC_Ctrl3 message);
    void newIC_Ctrl5Message(IC_Ctrl5 message);
    void newIC_Ctrl6Message(IC_Ctrl6 message);
    void newIC_Ctrl7Message(IC_Ctrl7 message);
    void error(CanErrorDetails errorDetails);

private:
    static const quint32 BMS_INFO1_ID = 0x68;
    static const quint32 IC_Ctrl1_ID = 0x102;
    static const quint32 IC_Ctrl2_ID = 0x103;
    static const quint32 IC_Ctrl3_ID = 0x120;
    static const quint32 IC_Ctrl5_ID = 0x300;
    static const quint32 IC_Ctrl6_ID = 0x308;
    static const quint32 IC_Ctrl7_ID = 0x310;

    void handle_BMS_INFO1(QByteArray payload);
    void handle_IC_Ctrl1(QByteArray payload);
    void handle_IC_Ctrl2(QByteArray payload);
    void handle_IC_Ctrl3(QByteArray payload);
    void handle_IC_Ctrl5(QByteArray payload);
    void handle_IC_Ctrl6(QByteArray payload);
    void handle_IC_Ctrl7(QByteArray payload);

#ifdef TESTING
public:
#endif
    bool extractBool(QByteArray bytes, int index);
};

#endif // CANFRAMEHANDLER_H
