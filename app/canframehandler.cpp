#include "canframehandler.h"

#include <QtEndian>
#include <iostream>

CanFrameHandler::CanFrameHandler(QObject *parent) : QObject(parent)
{

}

void CanFrameHandler::handleFrame(QCanBusFrame frame)
{
    switch (frame.frameId()) {
        case BMS_INFO1_ID:
            handle_BMS_INFO1(frame.payload());
            break;
        case IC_Ctrl1_ID:
            handle_IC_Ctrl1(frame.payload());
            break;
        case IC_Ctrl2_ID:
            handle_IC_Ctrl2(frame.payload());
            break;
        case IC_Ctrl3_ID:
            handle_IC_Ctrl3(frame.payload());
            break;
        case IC_Ctrl5_ID:
            handle_IC_Ctrl5(frame.payload());
            break;
        case IC_Ctrl6_ID:
            handle_IC_Ctrl6(frame.payload());
            break;
        case IC_Ctrl7_ID:
            handle_IC_Ctrl7(frame.payload());
            break;
    }
}

void CanFrameHandler::handle_BMS_INFO1(QByteArray payload) {
    quint16 current = qFromBigEndian<quint16>(payload.data() + 4);
    quint16 voltage = qFromBigEndian<quint16>(payload.data() + 6);
    BMS_INFO1 message {
        current, voltage
    };
    emit newBMS_INFO1Message(message);
}

void CanFrameHandler::handle_IC_Ctrl1(QByteArray payload) {
    quint8 soc = qFromBigEndian<quint8>(payload.data() + 2);
    // soc is unsigned so it cannot be < 0
    if (soc > 200) {
        emit error({CanErrorDetails::ErrorType::OUT_OF_RANGE, Signal::SOC, QVariant(soc / 2)});
    }
    quint8 engineTemp = qFromLittleEndian<quint8>(payload.data() + 3);
    quint16 speed = qFromBigEndian<quint16>(payload.data() + 4);
    quint8 vehicleModeRaw = qFromLittleEndian<quint8>(payload.data() + 7);
    VehicleMode vehicleMode = VehicleMode::UNKNOWN;
    if (vehicleModeRaw >= static_cast<int>(VehicleMode::INIT) && vehicleModeRaw <= static_cast<int>(VehicleMode::CONFIGURE)) {
        vehicleMode = static_cast<VehicleMode>(vehicleModeRaw);
    }
    else {
        emit error({CanErrorDetails::ErrorType::INAPPROPRIATE, Signal::VEHICLE_MODE, QVariant(vehicleModeRaw)});
    }
    IC_Ctrl1 message {
        .soc = soc, .engineTemp = engineTemp, .speed = speed, .vehicleMode = vehicleMode
    };
    emit newIC_Ctrl1Message(message);
}

void CanFrameHandler::handle_IC_Ctrl2(QByteArray payload)
{
    bool sportFlash = extractBool(payload, 32);
    bool standardFlash = extractBool(payload, 33);
    bool ecoFlash = extractBool(payload, 34);
    bool sportLit = extractBool(payload, 35);
    bool standardLit = extractBool(payload, 36);
    bool ecoLit = extractBool(payload, 37);
    IC_Ctrl2 message {
        .sportFlash = sportFlash, .standardFlash = standardFlash,
        .ecoFlash = ecoFlash, .sportLit = sportLit,
        .standardLit = standardLit, .ecoLit = ecoLit
    };
    emit newIC_Ctrl2Message(message);
}

void CanFrameHandler::handle_IC_Ctrl3(QByteArray payload)
{
    quint32 odometer = qFromBigEndian<quint32>(payload.data());
    IC_Ctrl3 message {
        .odometer = odometer
    };
    emit newIC_Ctrl3Message(message);
}

void CanFrameHandler::handle_IC_Ctrl5(QByteArray payload) {
    qint8 limitHeaters = qFromLittleEndian<quint8>(payload.data());
    bool keyInserted = extractBool(payload, 8);
    bool lockChargingPort = extractBool(payload, 9);
    bool unlockChargingPort = extractBool(payload, 10);
    bool fcContactor = extractBool(payload, 11);
    bool acRequest = extractBool(payload, 12);
    qint16 revSW = qFromLittleEndian<quint16>(payload.data() + 5);
    IC_Ctrl5 message {
        .limitHeaters = limitHeaters, .keyInserted = keyInserted,
        .lockChargingPort = lockChargingPort, .unlockChargingPort = unlockChargingPort,
        .fcContactor = fcContactor, .acRequest = acRequest,
        .revSW = revSW
    };
    emit newIC_Ctrl5Message(message);
}

void CanFrameHandler::handle_IC_Ctrl6(QByteArray payload)
{
    bool batLow = extractBool(payload, 0);
    bool batHigh = extractBool(payload, 1);
    bool checkEngine = extractBool(payload, 3);
    bool engineOverheat = extractBool(payload, 4);
    bool oil = extractBool(payload, 5);
    bool xBeep = extractBool(payload, 6);
    bool revLimit = extractBool(payload, 9);
    bool warmup = extractBool(payload, 11);
    bool ecm = extractBool(payload, 19);
    bool revFault = extractBool(payload, 21);
    bool drownMode = extractBool(payload, 22);
    bool throttleOpen = extractBool(payload, 23);
    bool noOil = extractBool(payload, 24);
    bool overheat = extractBool(payload, 25);
    bool knock = extractBool(payload, 26);
    bool throttleOpen2 = extractBool(payload, 29);
    bool visualShutdown = extractBool(payload, 32);
    bool visualShutdownHold = extractBool(payload, 34);
    bool checkKey = extractBool(payload, 48);
    bool accel = extractBool(payload, 51);
    bool badKey = extractBool(payload, 53);
    bool shutdown = extractBool(payload, 56);
    struct IC_Ctrl6 message {
        .batLow = batLow, .batHigh = batHigh,
        .checkEngine = checkEngine, .engineOverheat = engineOverheat,
        .oil = oil, .xBeep = xBeep, .revLimit = revLimit,
        .warmup = warmup, .ecm = ecm, .revFault = revFault,
        .drownMode = drownMode, .throttleOpen = throttleOpen,
        .noOil = noOil, .overheat = overheat, .knock = knock,
        .throttleOpen2 = throttleOpen2, .visualShutdown = visualShutdown,
        .visualShutdownHold = visualShutdownHold, .checkKey = checkKey,
        .accel = accel, .badKey = badKey, .shutdown = shutdown
    };
    emit newIC_Ctrl6Message(message);
}

void CanFrameHandler::handle_IC_Ctrl7(QByteArray payload)
{
    quint8 directionRaw = qFromLittleEndian<quint8>(payload.data());
    Direction direction = Direction::UNKNOWN;
    if (directionRaw >= static_cast<int>(Direction::OFF) && directionRaw <= static_cast<int>(Direction::REVERSE)) {
        direction = static_cast<Direction>(directionRaw);
    }
    IC_Ctrl7 message = {
        .direction = direction
    };
    emit newIC_Ctrl7Message(message);
}

bool CanFrameHandler::extractBool(QByteArray bytes, int bitIndex)
{
    int byteIndex = bitIndex / 8;
    int bitByteIndex = bitIndex - byteIndex * 8;
    unsigned char targetByte = bytes[byteIndex];
    unsigned char afterLeftShift = targetByte << (7 - bitByteIndex);
    unsigned char afterRightShift = afterLeftShift >> 7;
    return afterRightShift;
}

