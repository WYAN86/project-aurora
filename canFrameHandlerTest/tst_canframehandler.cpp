#define TESTING 1

#include <QtTest>
#include <QTest>
#include <QSignalSpy>
#include <QCanBusFrame>
#include <QtEndian>

#include "canmessages.h"
#include "canframehandler.h"

#include "canframehandler_test_data.cpp"

// add necessary includes here

Q_DECLARE_METATYPE(QCanBusFrame)
Q_DECLARE_METATYPE(CanErrorDetails)
Q_DECLARE_METATYPE(IC_Ctrl1)
Q_DECLARE_METATYPE(IC_Ctrl2)
Q_DECLARE_METATYPE(IC_Ctrl3)
Q_DECLARE_METATYPE(IC_Ctrl5)
Q_DECLARE_METATYPE(IC_Ctrl6)
Q_DECLARE_METATYPE(IC_Ctrl7)


class TestCanFrameHandler : public QObject
{
    Q_OBJECT

public:
    TestCanFrameHandler();
    ~TestCanFrameHandler();


private slots:
    void initTestCase();
    void cleanupTestCase();

    void extractBool();
    void extractBool_data();

    void test_IC_Ctrl1_signals_data();
    void test_IC_Ctrl1_signals();

    void test_IC_Ctrl2_signals_data();
    void test_IC_Ctrl2_signals();

    void test_IC_Ctrl3_signals_data();
    void test_IC_Ctrl3_signals();

    void test_IC_Ctrl5_signals_data();
    void test_IC_Ctrl5_signals();

    void test_IC_Ctrl6_signals_data();
    void test_IC_Ctrl6_signals();

    void test_IC_Ctrl7_signals_data();
    void test_IC_Ctrl7_signals();

    void test_BMS_INFO01_signals_data();
    void test_BMS_INFO01_signals();

private:
    CanFrameHandler* handler;

};

TestCanFrameHandler::TestCanFrameHandler()
{

}

TestCanFrameHandler::~TestCanFrameHandler()
{

}

void TestCanFrameHandler::initTestCase()
{
    handler = new CanFrameHandler();
    qRegisterMetaType<CanErrorDetails>();
}

void TestCanFrameHandler::cleanupTestCase()
{
    delete handler;
}

void TestCanFrameHandler::extractBool_data()
{
    QTest::addColumn<QByteArray>("bytes");
    QTest::addColumn<int>("index");
    QTest::addColumn<bool>("result");
    QTest::newRow("single byte beginning with 1") << QByteArray::fromHex("1") << 0 << true;
    QTest::newRow("single byte ending with 1") << QByteArray::fromHex("80") << 7 << true;
    QTest::newRow("single byte beginning with 0") << QByteArray::fromHex("FE") << 0 << false;
    QTest::newRow("single byte ending with 0") << QByteArray::fromHex("7F") << 7 << false;
    QTest::newRow("two bytes beginning with 1") << QByteArray::fromHex("0100") << 0 << true;
    QTest::newRow("two bytes ending with 1") << QByteArray::fromHex("0080") << 15 << true;
    QTest::newRow("two bytes 1 in the middle") << QByteArray::fromHex("0002") << 9 << true;
}

void TestCanFrameHandler::extractBool()
{
    QFETCH(QByteArray, bytes);
    QFETCH(int, index);
    QFETCH(bool, result);
    bool actualResult = handler->extractBool(bytes, index);
    QCOMPARE(actualResult, result);
}

void TestCanFrameHandler::test_IC_Ctrl1_signals_data()
{
    TestCanFrameHandlerData::IC_Ctrl1TestData();
}

void TestCanFrameHandler::test_IC_Ctrl1_signals()
{
    QSignalSpy spy_IC_Ctrl1(handler, SIGNAL(newIC_Ctrl1Message(IC_Ctrl1)));
    QSignalSpy spy_Error(handler, SIGNAL(error(CanErrorDetails)));


    QFETCH(QCanBusFrame, frame);
    QFETCH(bool, errorFrame);
    QFETCH(IC_Ctrl1, values);

    handler->handleFrame(frame);

    if(errorFrame) {
        QCOMPARE(spy_Error.count(), 1);
        CanErrorDetails error = spy_Error.first().at(0).value<CanErrorDetails>();

        if(error.signal == Signal::SOC) {
            QCOMPARE(error.value, floor(values.soc * 0.5) );
            QCOMPARE(error.type, CanErrorDetails::ErrorType::OUT_OF_RANGE);
        }
        else if(error.signal == Signal::VEHICLE_MODE) {
            QCOMPARE(error.type, CanErrorDetails::ErrorType::INAPPROPRIATE);
        }

    }

    QCOMPARE(spy_IC_Ctrl1.count(),  1);
    IC_Ctrl1 message = spy_IC_Ctrl1.first().at(0).value<IC_Ctrl1>();

    QCOMPARE(message.soc, values.soc);
    QCOMPARE(message.engineTemp, values.engineTemp);
    QCOMPARE(message.speed, values.speed);
    QCOMPARE(message.vehicleMode, values.vehicleMode);
}


void TestCanFrameHandler::test_IC_Ctrl2_signals_data()
{
    TestCanFrameHandlerData::IC_Ctrl2TestData();
}


void TestCanFrameHandler::test_IC_Ctrl2_signals()
{
    QSignalSpy spy_IC_Ctrl2(handler, SIGNAL(newIC_Ctrl2Message(IC_Ctrl2)));

    QFETCH(QCanBusFrame, frame);
    QFETCH(IC_Ctrl2, values);

    handler->handleFrame(frame);

    QCOMPARE(spy_IC_Ctrl2.count(),  1);
    IC_Ctrl2 message = spy_IC_Ctrl2.first().at(0).value<IC_Ctrl2>();


    QCOMPARE(message.sportFlash, values.sportFlash);

    QCOMPARE(message.sportLit, values.sportLit);

    QCOMPARE(message.standardFlash, values.standardFlash);

    QCOMPARE(message.standardLit, values.standardLit);

    QCOMPARE(message.ecoFlash, values.ecoFlash);

    QCOMPARE(message.ecoLit, values.ecoLit);

}

void TestCanFrameHandler::test_IC_Ctrl3_signals_data()
{
    TestCanFrameHandlerData::IC_Ctrl3TestData();
}


void TestCanFrameHandler::test_IC_Ctrl3_signals()
{
    QSignalSpy spy_IC_Ctrl3(handler, SIGNAL(newIC_Ctrl3Message(IC_Ctrl3)));

    QFETCH(QCanBusFrame, frame);
    QFETCH(IC_Ctrl3, values);

    handler->handleFrame(frame);

    QCOMPARE(spy_IC_Ctrl3.count(),  1);
    IC_Ctrl3 message = spy_IC_Ctrl3.first().at(0).value<IC_Ctrl3>();


    QCOMPARE(message.odometer, values.odometer);
}

void TestCanFrameHandler::test_IC_Ctrl5_signals_data()
{
    TestCanFrameHandlerData::IC_Ctrl5TestData();
}


void TestCanFrameHandler::test_IC_Ctrl5_signals()
{
    QSignalSpy spy_IC_Ctrl5(handler, SIGNAL(newIC_Ctrl5Message(IC_Ctrl5)));

    QFETCH(QCanBusFrame, frame);
    QFETCH(IC_Ctrl5, values);

    handler->handleFrame(frame);

    QCOMPARE(spy_IC_Ctrl5.count(),  1);
    IC_Ctrl5 message = spy_IC_Ctrl5.first().at(0).value<IC_Ctrl5>();


    QCOMPARE(message.limitHeaters, values.limitHeaters);

    QCOMPARE(message.keyInserted, values.keyInserted);

    QCOMPARE(message.lockChargingPort, values.lockChargingPort);

    QCOMPARE(message.unlockChargingPort, values.unlockChargingPort);

    QCOMPARE(message.fcContactor, values.fcContactor);

    QCOMPARE(message.revSW, values.revSW);

}

void TestCanFrameHandler::test_IC_Ctrl6_signals_data()
{
    TestCanFrameHandlerData::IC_Ctrl6TestData();
}


void TestCanFrameHandler::test_IC_Ctrl6_signals()
{
    QSignalSpy spy_IC_Ctrl6(handler, SIGNAL(newIC_Ctrl6Message(IC_Ctrl6)));

    QFETCH(QCanBusFrame, frame);
    QFETCH(IC_Ctrl6, values);

    handler->handleFrame(frame);

    QCOMPARE(spy_IC_Ctrl6.count(),  1);
    IC_Ctrl6 message = spy_IC_Ctrl6.first().at(0).value<IC_Ctrl6>();


    QCOMPARE(message.batLow, values.batLow);
    QCOMPARE(message.batHigh, values.batHigh);
    QCOMPARE(message.checkEngine, values.checkEngine);
    QCOMPARE(message.engineOverheat, values.engineOverheat);
    QCOMPARE(message.oil, values.oil);
    QCOMPARE(message.xBeep, values.xBeep);
    QCOMPARE(message.revLimit, values.revLimit);
    QCOMPARE(message.warmup, values.warmup);
    QCOMPARE(message.ecm, values.ecm);
    QCOMPARE(message.revFault, values.revFault);
    QCOMPARE(message.drownMode, values.drownMode);
    QCOMPARE(message.throttleOpen, values.throttleOpen);
    QCOMPARE(message.noOil, values.noOil);
    QCOMPARE(message.overheat, values.overheat);
    QCOMPARE(message.knock, values.knock);
    QCOMPARE(message.throttleOpen2, values.throttleOpen2);
    QCOMPARE(message.visualShutdown, values.visualShutdown);
    QCOMPARE(message.visualShutdownHold, values.visualShutdownHold);
    QCOMPARE(message.checkKey, values.checkKey);
    QCOMPARE(message.accel, values.accel);
    QCOMPARE(message.badKey, values.badKey);
    QCOMPARE(message.shutdown, values.shutdown);
}

void TestCanFrameHandler::test_IC_Ctrl7_signals_data()
{
    TestCanFrameHandlerData::IC_Ctrl7TestData();
}


void TestCanFrameHandler::test_IC_Ctrl7_signals()
{
    QSignalSpy spy_IC_Ctrl7(handler, SIGNAL(newIC_Ctrl7Message(IC_Ctrl7)));

    QFETCH(QCanBusFrame, frame);
    QFETCH(IC_Ctrl7, values);

    handler->handleFrame(frame);

    QCOMPARE(spy_IC_Ctrl7.count(),  1);
    IC_Ctrl7 message = spy_IC_Ctrl7.first().at(0).value<IC_Ctrl7>();


    QCOMPARE(message.direction, values.direction);
}

void TestCanFrameHandler::test_BMS_INFO01_signals_data()
{
    TestCanFrameHandlerData::BMS_INFO01TestData();
}


void TestCanFrameHandler::test_BMS_INFO01_signals()
{
    QSignalSpy spy_BMS_INFO1(handler, SIGNAL(newBMS_INFO1Message(BMS_INFO1)));

    QFETCH(QCanBusFrame, frame);
    QFETCH(BMS_INFO1, values);

    handler->handleFrame(frame);

    QCOMPARE(spy_BMS_INFO1.count(),  1);
    BMS_INFO1 message = spy_BMS_INFO1.first().at(0).value<BMS_INFO1>();


    QCOMPARE(message.current, values.current);
    QCOMPARE(message.voltage, values.voltage);
}

QTEST_GUILESS_MAIN(TestCanFrameHandler)

#include "tst_canframehandler.moc"
