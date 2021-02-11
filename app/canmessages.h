#ifndef CANMESSAGES_H
#define CANMESSAGES_H

#include <QObject>
#include <QVariant>

enum class VehicleMode {
    INIT = 0x0,
    IDLE = 0x1,
    CHARGE = 0x2,
    DRIVE = 0x3,
    ACTIVE = 0x4,
    SELFTEST = 0x5,
    SHUTDOWN = 0x6,
    TRAVERSE = 0x7,
    FAULT = 0x8,
    CONFIGURE = 0x9,
    UNKNOWN
};
Q_DECLARE_METATYPE(VehicleMode)

enum class Direction {
    OFF = 0x0,
    FORWARD = 0x1,
    REVERSE = 0x2,
    UNKNOWN
};
Q_DECLARE_METATYPE(Direction)

typedef struct {
    quint16 current, voltage;
} BMS_INFO1;
Q_DECLARE_METATYPE(BMS_INFO1)

typedef struct {
    quint8 soc, engineTemp;
    quint16 speed;
    VehicleMode vehicleMode;
} IC_Ctrl1;

typedef struct {
    bool sportFlash, standardFlash, ecoFlash,
        sportLit, standardLit, ecoLit;
} IC_Ctrl2;

typedef struct {
    quint32 odometer;
} IC_Ctrl3;

typedef struct {
    qint8 limitHeaters;
    bool keyInserted, lockChargingPort, unlockChargingPort,
        fcContactor, acRequest;
    qint16 revSW;
} IC_Ctrl5;

typedef struct IC_Ctrl6 {
    bool batLow, batHigh, checkEngine, engineOverheat,
        oil, xBeep, revLimit, warmup, ecm, revFault,
        drownMode, throttleOpen, noOil, overheat,
        knock, throttleOpen2, visualShutdown, visualShutdownHold,
        checkKey, accel, badKey, shutdown;
} IC_Ctrl6;

typedef struct IC_Ctrl7 {
    Direction direction;
} IC_Ctrl7;

enum class Signal {
    SOC, VEHICLE_MODE, DIRECTION
};

typedef struct CanErrorDetails {
    enum class ErrorType {
        OUT_OF_RANGE, INAPPROPRIATE, OTHER
    };
    ErrorType type;
    Signal signal;
    QVariant value;
} CanErrorDetails;


#endif // CANMESSAGES_H
