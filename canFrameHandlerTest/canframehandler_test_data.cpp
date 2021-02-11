#include <QtTest>
#include <QTest>
#include <QCanBusFrame>

#include "canmessages.h"

// add necessary includes here


class TestCanFrameHandlerData : public QObject
{
    Q_OBJECT

public:
    TestCanFrameHandlerData();
    ~TestCanFrameHandlerData();

    static void IC_Ctrl1TestData();
    static void IC_Ctrl2TestData();
    static void IC_Ctrl3TestData();
    static void IC_Ctrl5TestData();
    static void IC_Ctrl6TestData();
    static void IC_Ctrl7TestData();
    static void BMS_INFO01TestData();
};


void TestCanFrameHandlerData::IC_Ctrl1TestData()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<bool>("errorFrame");
    QTest::addColumn<IC_Ctrl1>("values");
    // Soc value test cases
    QTest::newRow("soc signal with raw soc value 10")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 0A 00 0000 00 00"))<< false << IC_Ctrl1 {
                                                          .soc = 10, .engineTemp = 0, .speed =0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("soc signal with raw soc value 0")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 0000 00 00"))<< false << IC_Ctrl1 {
                                                         .soc = 0, .engineTemp = 0, .speed =0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("soc signal with raw soc value 200")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 C8 00 0000 00 00"))<< false << IC_Ctrl1 {
                                                            .soc = 200, .engineTemp = 0, .speed =0, .vehicleMode = VehicleMode::INIT};

    // Error soc value
    QTest::newRow("soc signal with raw max soc value 255")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 FF 00 0000 00 00"))<< true << IC_Ctrl1 {
                                                               .soc = 255, .engineTemp = 0, .speed =0, .vehicleMode = VehicleMode::INIT};


    // Engine temp test cases
    QTest::newRow("engine temp signal with raw temp value 10")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 0A 0000 00 00")) << false << IC_Ctrl1 {
                                                                   .soc = 0, .engineTemp = 10, .speed =0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("engine temp signal with raw temp value 0")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 0000 00 00")) << false << IC_Ctrl1 {
                                                                  .soc = 0, .engineTemp = 0, .speed =0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("engine temp signal with raw temp value 100")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 64 0000 00 00")) << false << IC_Ctrl1 {
                                                                    .soc = 0, .engineTemp = 100, .speed =0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("engine temp signal with raw temp value 250")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 FA 0000 00 00")) << false << IC_Ctrl1 {
                                                                    .soc = 0, .engineTemp = 250, .speed =0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("engine temp signal with raw max temp value 255")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 FF 0000 00 00")) << false << IC_Ctrl1 {
                                                                        .soc = 0, .engineTemp = 255, .speed =0, .vehicleMode = VehicleMode::INIT};

    // Speed test cases
    QTest::newRow("speed signal with raw speed value 10")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 000A 00 00"))<< false << IC_Ctrl1 {
                                                              .soc = 0, .engineTemp = 0, .speed = 10, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("speed signal with raw speed value 0")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 0000 00 00"))<< false << IC_Ctrl1 {
                                                             .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("speed signal with raw speed value 100")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 0064 00 00"))<< false << IC_Ctrl1 {
                                                               .soc = 0, .engineTemp = 0, .speed = 100, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("speed signal with raw speed value 1000")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 03E8 00 00"))<< false << IC_Ctrl1 {
                                                                .soc = 0, .engineTemp = 0, .speed = 1000, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("speed signal with raw speed value 5000")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 1388 00 00"))<< false << IC_Ctrl1 {
                                                                .soc = 0, .engineTemp = 0, .speed = 5000, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("speed signal with raw max speed value 65535")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 FFFF 00 00"))<< false << IC_Ctrl1 {
                                                                     .soc = 0, .engineTemp = 0, .speed = 65535, .vehicleMode = VehicleMode::INIT};

    // Vehicle mode test cases
    QTest::newRow("vehicle mode signal init")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 00 00 0000 00 00")) << false << IC_Ctrl1 {
                                                  .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::INIT};
    QTest::newRow("vehicle mode signal idle")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 01")) <<false << IC_Ctrl1 {
                                                  .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::IDLE};
    QTest::newRow("vehicle mode signal charge")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 02")) << false << IC_Ctrl1 {
                                                    .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::CHARGE};
    QTest::newRow("vehicle mode signal drive")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 03")) << false << IC_Ctrl1 {
                                                   .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::DRIVE};
    QTest::newRow("vehicle mode signal active")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 04")) << false << IC_Ctrl1 {
                                                    .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::ACTIVE};
    QTest::newRow("vehicle mode signal selftest")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 05")) << false << IC_Ctrl1 {
                                                      .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::SELFTEST};
    QTest::newRow("vehicle mode signal shutdown")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 06")) << false << IC_Ctrl1 {
                                                      .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::SHUTDOWN};
    QTest::newRow("vehicle mode signal traverse")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 07")) << false << IC_Ctrl1 {
                                                      .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::TRAVERSE};
    QTest::newRow("vehicle mode signal fault")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 08")) << false << IC_Ctrl1 {
                                                   .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::FAULT};
    QTest::newRow("vehicle mode signal configure")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 0009")) << false << IC_Ctrl1 {
                                                       .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::CONFIGURE};
    QTest::newRow("vehicle mode signal unknown")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 15")) << true << IC_Ctrl1 {
                                                     .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::UNKNOWN};
    QTest::newRow("vehicle mode signal max value unknown")  << QCanBusFrame(0x102, QByteArray::fromHex("000A 00 00 0000 00 FF")) << true << IC_Ctrl1 {
                                                     .soc = 0, .engineTemp = 0, .speed = 0, .vehicleMode = VehicleMode::UNKNOWN};

    // Combination of values
    QTest::newRow("signal with multiple values 1")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 54 78 0020 00 03"))<< false << IC_Ctrl1 {
                                                          .soc = 84, .engineTemp = 120, .speed = 32, .vehicleMode = VehicleMode::DRIVE};

    QTest::newRow("signal with multiple values 2")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 10 32 0000 00 02"))<< false << IC_Ctrl1 {
                                                          .soc = 16, .engineTemp = 50, .speed = 0, .vehicleMode = VehicleMode::CHARGE};

    QTest::newRow("signal with multiple values 3")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 B6 C8 04B0 00 05"))<< false << IC_Ctrl1 {
                                                          .soc = 182, .engineTemp = 200, .speed = 1200, .vehicleMode = VehicleMode::SELFTEST};

    QTest::newRow("signal with multiple values and error ")  << QCanBusFrame(0x102, QByteArray::fromHex("FFFF CD 3C 0003 00 01"))<< true << IC_Ctrl1 {
                                                                .soc = 205, .engineTemp = 60, .speed = 3, .vehicleMode = VehicleMode::IDLE};
}

void TestCanFrameHandlerData::IC_Ctrl2TestData()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<IC_Ctrl2>("values");

    // Sport flash signals
    QTest::newRow("Sport flash 1")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 01")) << IC_Ctrl2{
                                       .sportFlash = true, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                       .standardLit = false, .ecoLit = false};

    QTest::newRow("Sport flash 0")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 00")) <<  IC_Ctrl2{
                                       .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                       .standardLit = false, .ecoLit = false};
    // Standard flash signals
    QTest::newRow("Standard flash 1")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 02")) <<  IC_Ctrl2{
                                          .sportFlash = false, .standardFlash = true, .ecoFlash = false, .sportLit = false,
                                          .standardLit = false, .ecoLit = false};
    QTest::newRow("Standard flash 0")  << QCanBusFrame(0x103, QByteArray::fromHex("00AA5000 00")) <<  IC_Ctrl2{
                                          .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                          .standardLit = false, .ecoLit = false};

    // Eco flash signals
    QTest::newRow("Eco flash 1")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 04")) <<  IC_Ctrl2{
                                     .sportFlash = false, .standardFlash = false, .ecoFlash = true, .sportLit = false,
                                     .standardLit = false, .ecoLit = false};
    QTest::newRow("Eco flash 0")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 00")) <<  IC_Ctrl2{
                                     .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                     .standardLit = false, .ecoLit = false};

    // Sport lit signal
    QTest::newRow("Sport lit 1")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 08")) <<  IC_Ctrl2{
                                     .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = true,
                                     .standardLit = false, .ecoLit = false};
    QTest::newRow("Sport lit 0")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 00")) <<  IC_Ctrl2{
                                     .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                     .standardLit = false, .ecoLit = false};
    // Standard lit signal
    QTest::newRow("Standard lit 1")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 10")) <<  IC_Ctrl2{
                                        .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                        .standardLit = true, .ecoLit = false};
    QTest::newRow("Standard lit 0")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 00")) <<  IC_Ctrl2{
                                        .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                        .standardLit = false, .ecoLit = false};

    // Eco lit signal
    QTest::newRow("Eco lit 1")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 20"))<<  IC_Ctrl2{
                                   .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                   .standardLit = false, .ecoLit = true};
    QTest::newRow("Eco lit 0")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 00"))<<  IC_Ctrl2{
                                   .sportFlash = false, .standardFlash = false, .ecoFlash = false, .sportLit = false,
                                   .standardLit = false, .ecoLit = false};

    //Multiple signals
    QTest::newRow("Multiple signals 1")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 03"))<<  IC_Ctrl2{
                                   .sportFlash = true, .standardFlash = true, .ecoFlash = false, .sportLit = false,
                                   .standardLit = false, .ecoLit = false};

    QTest::newRow("Multiple signals 2")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 24"))<<  IC_Ctrl2{
                                   .sportFlash = false, .standardFlash = false, .ecoFlash = true, .sportLit = false,
                                   .standardLit = false, .ecoLit = true};

    QTest::newRow("Multiple signals 3")  << QCanBusFrame(0x103, QByteArray::fromHex("00000000 FF"))<<  IC_Ctrl2{
                                   .sportFlash = true, .standardFlash = true, .ecoFlash = true, .sportLit = true,
                                   .standardLit = true, .ecoLit = true};
}

void TestCanFrameHandlerData::IC_Ctrl3TestData()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<IC_Ctrl3>("values");

    // Odometer signals
    QTest::newRow("Odometer with value 10")  << QCanBusFrame(0x120, QByteArray::fromHex("0000000A 00")) << IC_Ctrl3{ .odometer = 10};

    QTest::newRow("Odometer with value 0")  << QCanBusFrame(0x120, QByteArray::fromHex("00000000 00")) <<  IC_Ctrl3{ .odometer = 0};

    QTest::newRow("Odometer with value 1000")  << QCanBusFrame(0x120, QByteArray::fromHex("000003E8 00")) <<  IC_Ctrl3{ .odometer = 1000};

    QTest::newRow("Odometer with value 254524")  << QCanBusFrame(0x120, QByteArray::fromHex("0003E23C 00")) <<  IC_Ctrl3{ .odometer = 254524};

    QTest::newRow("Odometer with value 172339932")  << QCanBusFrame(0x120, QByteArray::fromHex("0A45B2DC 00")) <<  IC_Ctrl3{ .odometer = 172339932};

    QTest::newRow("Odometer with value 4294967295")  << QCanBusFrame(0x120, QByteArray::fromHex("FFFFFFFF 00")) <<  IC_Ctrl3{ .odometer = 4294967295};
}

void TestCanFrameHandlerData::IC_Ctrl5TestData()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<IC_Ctrl5>("values");

    // Limit heater signals
    QTest::newRow("Limit heater with value 100")  << QCanBusFrame(0x300, QByteArray::fromHex("64 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 100, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("Limit heater with value 0")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("Limit heater with value 127")  << QCanBusFrame(0x300, QByteArray::fromHex("7F 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 127, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("Limit heater with value -128")  << QCanBusFrame(0x300, QByteArray::fromHex("80 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = -128, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    // Key inserted signals
    QTest::newRow("Key inserted 1")  << QCanBusFrame(0x300, QByteArray::fromHex("00 01 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = true,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("Key inserted 0")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    // Lock charging port signals
    QTest::newRow("Lock port 1")  << QCanBusFrame(0x300, QByteArray::fromHex("00 02 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = true, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("Lock port 0")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    // Unlock charging port signals
    QTest::newRow("Unlock port 1")  << QCanBusFrame(0x300, QByteArray::fromHex("00 04 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = true,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("Unlock port 0")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    // Fc contactor signals
    QTest::newRow("FcContactor 1")  << QCanBusFrame(0x300, QByteArray::fromHex("00 08 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = true, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("FcContactor 0")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    // Ac request Signals
    QTest::newRow("Ac request 1")  << QCanBusFrame(0x300, QByteArray::fromHex("00 10 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = true,
                                       .revSW = 0 };

    QTest::newRow("Ac request 0")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 000000 00")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    // revSw signals
    QTest::newRow("Rew sw with value 100")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 00000 6400")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 100 };

    QTest::newRow("Rew sw with value 0")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 00000 0000")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 0 };

    QTest::newRow("Rew sw with value 32 767")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 00000 FF7F")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = 32767 };

    QTest::newRow("Rew sw with value -32 768")  << QCanBusFrame(0x300, QByteArray::fromHex("00 00 00000 0080")) << IC_Ctrl5{
                                       .limitHeaters = 0, .keyInserted = false,
                                       .lockChargingPort = false, .unlockChargingPort = false,
                                       .fcContactor = false, .acRequest = false,
                                       .revSW = -32768 };
}

void TestCanFrameHandlerData::IC_Ctrl6TestData()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<IC_Ctrl6>("values");

    // Bat low signals
    QTest::newRow("Bat low 1")  << QCanBusFrame(0x308, QByteArray::fromHex("01 00 00 00 00 00 00 00 00")) << IC_Ctrl6 {
                                       .batLow = true, .batHigh = false,
                                       .checkEngine = false, .engineOverheat = false,
                                       .oil = false, .xBeep = false, .revLimit = false,
                                       .warmup = false, .ecm = false, .revFault = false,
                                       .drownMode = false, .throttleOpen = false,
                                       .noOil = false, .overheat = false, .knock = false,
                                       .throttleOpen2 = false, .visualShutdown = false,
                                       .visualShutdownHold = false, .checkKey = false,
                                       .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Bat low 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<   IC_Ctrl6 {
                                       .batLow = false, .batHigh = false,
                                       .checkEngine = false, .engineOverheat = false,
                                       .oil = false, .xBeep = false, .revLimit = false,
                                       .warmup = false, .ecm = false, .revFault = false,
                                       .drownMode = false, .throttleOpen = false,
                                       .noOil = false, .overheat = false, .knock = false,
                                       .throttleOpen2 = false, .visualShutdown = false,
                                       .visualShutdownHold = false, .checkKey = false,
                                       .accel = false, .badKey = false, .shutdown = false};
    // Bat high signals
    QTest::newRow("Bat high 1")  << QCanBusFrame(0x308, QByteArray::fromHex("02 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                      .batLow = false, .batHigh = true,
                                      .checkEngine = false, .engineOverheat = false,
                                      .oil = false, .xBeep = false, .revLimit = false,
                                      .warmup = false, .ecm = false, .revFault = false,
                                      .drownMode = false, .throttleOpen = false,
                                      .noOil = false, .overheat = false, .knock = false,
                                      .throttleOpen2 = false, .visualShutdown = false,
                                      .visualShutdownHold = false, .checkKey = false,
                                      .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Bat high 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<   IC_Ctrl6 {
                                       .batLow = false, .batHigh = false,
                                       .checkEngine = false, .engineOverheat = false,
                                       .oil = false, .xBeep = false, .revLimit = false,
                                       .warmup = false, .ecm = false, .revFault = false,
                                       .drownMode = false, .throttleOpen = false,
                                       .noOil = false, .overheat = false, .knock = false,
                                       .throttleOpen2 = false, .visualShutdown = false,
                                       .visualShutdownHold = false, .checkKey = false,
                                       .accel = false, .badKey = false, .shutdown = false};

    // Check engine signals
    QTest::newRow("Check engine 1")  << QCanBusFrame(0x308, QByteArray::fromHex("08 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = true, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Check engine 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Engine overheat signals
    QTest::newRow("Engine overheat 1")  << QCanBusFrame(0x308, QByteArray::fromHex("10 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = true,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Engine overheat 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Oil signals
    QTest::newRow("Oil 1")  << QCanBusFrame(0x308, QByteArray::fromHex("20 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = true, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Oil 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // XBeep signals
    QTest::newRow("xBeep 1")  << QCanBusFrame(0x308, QByteArray::fromHex("40 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = true, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("xBeep 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // RevLimit signals
    QTest::newRow("RevLimit 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 02 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = true,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("RevLimit  0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Warmup signals
    QTest::newRow("Warmup 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 08 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = true, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Warmup 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Ecm signals
    QTest::newRow("Ecm 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 08 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = true, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Ecm 0")  << QCanBusFrame(0x308, QByteArray::fromHex("000 000 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};


    // Rev fault signals
    QTest::newRow("Rev fault 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 20 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = true,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Rev fault 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};


    // Drown mode signals
    QTest::newRow("Drown mode 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 40 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = true, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Drown mode 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Throttle open signals
    QTest::newRow("Throttle open 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 80 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = true,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Throttle open 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // No oil signals
    QTest::newRow("No oil 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 01 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = true, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("No oil 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Overheat signals
    QTest::newRow("Overheat 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 02 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = true, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Overheat 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Knock signals
    QTest::newRow("Knock 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 04 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = true,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Knock 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Throttle open 2 signals
    QTest::newRow("Throttle open2 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 20 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = true, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Throttle open2 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Visual shutdown signals
    QTest::newRow("Visual shutdown 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 01 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = true,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Visual shutdown 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Visual shutdown hold signals
    QTest::newRow("Visual shutdown hold 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 04 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = true, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Visual shutdown hold 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Check key signals
    QTest::newRow("Check key 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 01 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = true,
                                        .accel = false, .badKey = false, .shutdown = false};

    QTest::newRow("Check key 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Accel signals
    QTest::newRow("Accel 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 08 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = true, .badKey = false, .shutdown = false};

    QTest::newRow("Accel 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Bad key signals
    QTest::newRow("Bad Key 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 20 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = true, .shutdown = false};

    QTest::newRow("Bad key 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};

    // Shutdown signals
    QTest::newRow("Shutdown 1")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 01 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = true};

    QTest::newRow("Shutdown 0")  << QCanBusFrame(0x308, QByteArray::fromHex("00 00 00 00 00 00 00 00 00")) <<  IC_Ctrl6 {
                                        .batLow = false, .batHigh = false,
                                        .checkEngine = false, .engineOverheat = false,
                                        .oil = false, .xBeep = false, .revLimit = false,
                                        .warmup = false, .ecm = false, .revFault = false,
                                        .drownMode = false, .throttleOpen = false,
                                        .noOil = false, .overheat = false, .knock = false,
                                        .throttleOpen2 = false, .visualShutdown = false,
                                        .visualShutdownHold = false, .checkKey = false,
                                        .accel = false, .badKey = false, .shutdown = false};
}

void TestCanFrameHandlerData::IC_Ctrl7TestData()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<IC_Ctrl7>("values");

    QTest::newRow("Direction off")  << QCanBusFrame(0x310, QByteArray::fromHex("00 0000"))
                                    << IC_Ctrl7 {Direction::OFF};

    QTest::newRow("Direction forward")  << QCanBusFrame(0x310, QByteArray::fromHex("01 0000"))
                                        << IC_Ctrl7 {Direction::FORWARD};

    QTest::newRow("Direction reverse")  << QCanBusFrame(0x310, QByteArray::fromHex("02 0000"))
                                        << IC_Ctrl7 {Direction::REVERSE};

    QTest::newRow("Direction with invalid value")  << QCanBusFrame(0x310, QByteArray::fromHex("FF 0000"))
                                                   << IC_Ctrl7 {Direction::UNKNOWN};
}

void TestCanFrameHandlerData::BMS_INFO01TestData()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<BMS_INFO1>("values");

    // Current frames
    QTest::newRow("Current with value 10")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000 000A 0000 00"))
                                    << BMS_INFO1 {10, 0};
    QTest::newRow("Current with value 0")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000 0000 0000 00"))
                                    << BMS_INFO1 {0, 0};
    QTest::newRow("Current with value 5000")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000 1388 0000 00"))
                                    << BMS_INFO1 {5000, 0};
    QTest::newRow("Current with max value 65535")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000 FFFF 0000 00"))
                                    << BMS_INFO1 {65535, 0};

    // Voltage frames
    QTest::newRow("Voltage with value 10")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000 0000 000A 00"))
                                    << BMS_INFO1 {0, 10};
    QTest::newRow("Voltage with value 0")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000 0000 0000 00"))
                                    << BMS_INFO1 {0, 0};
    QTest::newRow("Voltage with value 5000")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000  0000 1388 00"))
                                    << BMS_INFO1 {0, 5000};
    QTest::newRow("Voltage with max value 65535")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000  0000 FFFF 00"))
                                    << BMS_INFO1 {0, 65535};

    // Both values in frame
    QTest::newRow("Multiple values 1")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000 00F5 0093 00"))
                                    << BMS_INFO1 {245, 147};

    QTest::newRow("Multiple values 2")  << QCanBusFrame(0x68, QByteArray::fromHex("0000 0000  0001 1232 00"))
                                    << BMS_INFO1 {1, 4658};

}
