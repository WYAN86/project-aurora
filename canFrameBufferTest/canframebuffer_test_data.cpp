#include <QtTest>
#include <QTest>

#include "canmessages.h"

// add necessary includes here

Q_DECLARE_METATYPE(IC_Ctrl1)
Q_DECLARE_METATYPE(IC_Ctrl2)
Q_DECLARE_METATYPE(IC_Ctrl3)
Q_DECLARE_METATYPE(IC_Ctrl5)
Q_DECLARE_METATYPE(IC_Ctrl6)
Q_DECLARE_METATYPE(IC_Ctrl7)


class TestCanSignalBufferData : public QObject
{
    Q_OBJECT

public:
    TestCanSignalBufferData();
    ~TestCanSignalBufferData();

    //Bms_info
    static void currentTestData();
    static void voltageTestData();
    static void powerTestData();

    //Ic_ctrl1
    static void socTestData();
    static void engineTempTestData();
    static void speedTestData();
    static void vehicleModeTestData();

    //Ic_ctrl2
    static void sportFlashTestData();
    static void standardFlashTestData();
    static void ecoFlashTestData();
    static void sportLitTestData();
    static void standardLitTestData();
    static void ecoLitTestData();

    //Ic_ctrl3
    static void odometerTestData();

    //Ic_ctrl5
    static void limitHeatersTestData();
    static void keyInsertedTestData();
    static void lockChargingPortTestData();
    static void unlockChargingPortTestData();
    static void fcContactorTestData();
    static void acRequestTestData();
    static void revSWTestData();

    //Ic_ctrl7
    static void directionTestData();

    //Average calculations
    static void speedAverageTestData();
    static void engineTempAverageTestData();
    static void socAverageTestData();
    static void limitHeatersAverageTestData();
    static void revSWAverageTestData();
    static void voltageAverageTestData();
    static void currentAverageTestData();

    //Update power history signal
    static void powerHistoryTestData();

private:
    static float calculate_moving_average(int value1, int value2, int value3);
};

void TestCanSignalBufferData::currentTestData()
{
    QTest::addColumn<BMS_INFO1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addRow("current 1")<< BMS_INFO1 {0, 0,} << QVariant::fromValue<float>((0 * 0.1) - 1000);
    QTest::addRow("current 2")<< BMS_INFO1 {50, 0,} <<  QVariant::fromValue<float>((50 * 0.1) - 1000);
    QTest::addRow("current 3")<< BMS_INFO1 {100, 0,} <<  QVariant::fromValue<float>(( 100 * 0.1) - 1000);
}

void TestCanSignalBufferData::voltageTestData()
{
    QTest::addColumn<BMS_INFO1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addRow("Voltage 1")<< BMS_INFO1 {0, 0,} << QVariant::fromValue<float>(0 * 0.1);
    QTest::addRow("Voltage 2")<< BMS_INFO1 {0, 50} << QVariant::fromValue<float>(50 * 0.1);
    QTest::addRow("Voltage 3")<< BMS_INFO1 {0, 100} << QVariant::fromValue<float>(100 * 0.1);
}

void TestCanSignalBufferData::powerTestData()
{
    QTest::addColumn<BMS_INFO1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addRow("Power 1")<< BMS_INFO1 {10000, 15} << QVariant::fromValue<float>(0);
    QTest::addRow("Power 2")<< BMS_INFO1 {127, 56} << QVariant::fromValue<float>(abs(((127.000 * 0.1) - 1000) * (56.000 * 0.1)));
    QTest::addRow("Power 3")<< BMS_INFO1 {524, 0} << QVariant::fromValue<float>(0);
    QTest::addRow("Power 4")<< BMS_INFO1 {227, 226} << QVariant::fromValue<float>(abs(((227.000 * 0.1) - 1000) * (226.000 * 0.1)));
}

void TestCanSignalBufferData::socTestData()
{
    QTest::addColumn<IC_Ctrl1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addRow("Soc 1")<< IC_Ctrl1 {0, 0, 0, VehicleMode::UNKNOWN} << QVariant::fromValue<float>(0 * 0.5);
    QTest::addRow("Soc 2")<< IC_Ctrl1 {50, 0, 0, VehicleMode::UNKNOWN} << QVariant::fromValue<float>(50 * 0.5);
    QTest::addRow("Soc 3")<< IC_Ctrl1 {200, 0, 0, VehicleMode::UNKNOWN} << QVariant::fromValue<float>(200 * 0.5);
}

void TestCanSignalBufferData::engineTempTestData()
{
    QTest::addColumn<IC_Ctrl1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addRow("Engine temp 1")<< IC_Ctrl1 {0, 0, 0, VehicleMode::UNKNOWN} << QVariant::fromValue<quint8>(0 );
    QTest::addRow("Engine temp 2")<< IC_Ctrl1 {0, 50, 0, VehicleMode::UNKNOWN} << QVariant::fromValue<quint8>(50 );
    QTest::addRow("Engine temp 3")<< IC_Ctrl1 {0, 250, 0, VehicleMode::UNKNOWN} << QVariant::fromValue<quint8>(250 );
}

void TestCanSignalBufferData::speedTestData()
{
    QTest::addColumn<IC_Ctrl1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addColumn<IC_Ctrl1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addRow("Speed 1")<< IC_Ctrl1 {0, 0, 0, VehicleMode::UNKNOWN} << QVariant::fromValue<float>(0 * 0.1);
    QTest::addRow("Speed 2")<< IC_Ctrl1 {0, 0, 250, VehicleMode::UNKNOWN} << QVariant::fromValue<float>(250 * 0.1);
    QTest::addRow("Speed 3")<< IC_Ctrl1 {0, 0, 500, VehicleMode::UNKNOWN} << QVariant::fromValue<float>(500 * 0.1);
    QTest::addRow("Speed 4")<< IC_Ctrl1 {0, 0, 1000, VehicleMode::UNKNOWN} << QVariant::fromValue<float>(1000 * 0.1);
}

void TestCanSignalBufferData::vehicleModeTestData()
{
    QTest::addColumn<IC_Ctrl1>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::INIT} << QVariant::fromValue<VehicleMode>(VehicleMode::INIT );
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::IDLE} << QVariant::fromValue<VehicleMode>(VehicleMode::IDLE );
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::DRIVE} << QVariant::fromValue<VehicleMode>(VehicleMode::DRIVE);
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::ACTIVE} << QVariant::fromValue<VehicleMode>(VehicleMode::ACTIVE);
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::SELFTEST} << QVariant::fromValue<VehicleMode>(VehicleMode::SELFTEST);
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::SHUTDOWN} << QVariant::fromValue<VehicleMode>(VehicleMode::SHUTDOWN);
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::TRAVERSE} << QVariant::fromValue<VehicleMode>(VehicleMode::TRAVERSE);
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::FAULT} << QVariant::fromValue<VehicleMode>(VehicleMode::FAULT);
    QTest::addRow("Vehicle")<< IC_Ctrl1 {0, 0, 0, VehicleMode::CONFIGURE} << QVariant::fromValue<VehicleMode>(VehicleMode::CONFIGURE);
}

void TestCanSignalBufferData::sportFlashTestData()
{
    QTest::addColumn<IC_Ctrl2>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Sport flash true") << IC_Ctrl2{ true,  false, false, false, false, false} << QVariant::fromValue<bool>(true);
    QTest::newRow("Sport flash false") << IC_Ctrl2{ false,  false, false, false, false, false} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::standardFlashTestData()
{
    QTest::addColumn<IC_Ctrl2>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Standard flash true") << IC_Ctrl2{ false,  true, false, false, false, false} << QVariant::fromValue<bool>(true);
    QTest::newRow("Standard flash false") << IC_Ctrl2{ false,  false, false, false, false, false} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::ecoFlashTestData()
{
    QTest::addColumn<IC_Ctrl2>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Eco flash true") << IC_Ctrl2{ false,  false, true, false, false, false} << QVariant::fromValue<bool>(true);
    QTest::newRow("Eco flash false") << IC_Ctrl2{ false,  false, false, false, false, false} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::sportLitTestData()
{
    QTest::addColumn<IC_Ctrl2>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Sport lit true") << IC_Ctrl2{ false,  false, false, true, false, false} << QVariant::fromValue<bool>(true);
    QTest::newRow("Sport lit false") << IC_Ctrl2{ false,  false, false, false, false, false} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::standardLitTestData()
{
    QTest::addColumn<IC_Ctrl2>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Standard lit true") << IC_Ctrl2{ false,  false, false, false, true, false} << QVariant::fromValue<bool>(true);
    QTest::newRow("Standard lit false") << IC_Ctrl2{ false,  false, false, false, false, false} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::ecoLitTestData()
{
    QTest::addColumn<IC_Ctrl2>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Eco lit true") << IC_Ctrl2{ false,  false, false, false, false, true} << QVariant::fromValue<bool>(true);
    QTest::newRow("Eco lit false") << IC_Ctrl2{ false,  false, false, false, false, false} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::odometerTestData()
{
    QTest::addColumn<IC_Ctrl3>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Odometer 10") << IC_Ctrl3{10} << QVariant::fromValue<double>(10 * 0.1);
    QTest::newRow("Odometer 1000") << IC_Ctrl3{1000} << QVariant::fromValue<double>(1000 * 0.1);
    QTest::newRow("Odometer 5000") << IC_Ctrl3{50000} << QVariant::fromValue<double>(50000 * 0.1);
    QTest::newRow("Odometer 10") << IC_Ctrl3{1234567} << QVariant::fromValue<double>(1234567 * 0.1);
}

void TestCanSignalBufferData::limitHeatersTestData()
{
    QTest::addColumn<IC_Ctrl5>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Limit heaters 0") << IC_Ctrl5{0, false, false, false, false, false, 0} << QVariant::fromValue<qint16>(0);
    QTest::newRow("Limit heaters 100") << IC_Ctrl5{100, false, false, false, false, false, 0} << QVariant::fromValue<qint16>(100);
    QTest::newRow("Limit heaters 125") << IC_Ctrl5{125, false, false, false, false, false, 0} << QVariant::fromValue<qint16>(125);
}

void TestCanSignalBufferData::keyInsertedTestData()
{
    QTest::addColumn<IC_Ctrl5>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Key inserted true") << IC_Ctrl5{0, true, false, false, false, false, 0} << QVariant::fromValue<bool>(true);
    QTest::newRow("Key inserted false") << IC_Ctrl5{0, false, false, false, false, false, 0} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::lockChargingPortTestData()
{
    QTest::addColumn<IC_Ctrl5>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Lock port true") << IC_Ctrl5{0, false, true, false, false, false, 0} << QVariant::fromValue<bool>(true);
    QTest::newRow("Lock port false") << IC_Ctrl5{0, false, false, false, false, false, 0} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::unlockChargingPortTestData()
{
    QTest::addColumn<IC_Ctrl5>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Unlock port true") << IC_Ctrl5{0, false, false, true, false, false, 0} << QVariant::fromValue<bool>(true);
    QTest::newRow("Unlock port false") << IC_Ctrl5{0, false, false, false, false, false, 0} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::fcContactorTestData()
{
    QTest::addColumn<IC_Ctrl5>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Fc contactor true") << IC_Ctrl5{0, false, false, false, true, false, 0} << QVariant::fromValue<bool>(true);
    QTest::newRow("Fc contactor false") << IC_Ctrl5{0, false, false, false, false, false, 0} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::acRequestTestData()
{
    QTest::addColumn<IC_Ctrl5>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Ac request true") << IC_Ctrl5{0, false, false, false, false, true, 0} << QVariant::fromValue<bool>(true);
    QTest::newRow("Ac request false") << IC_Ctrl5{0, false, false, false, false, false, 0} << QVariant::fromValue<bool>(false);
}

void TestCanSignalBufferData::revSWTestData()
{
    QTest::addColumn<IC_Ctrl5>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("RevSw 0") << IC_Ctrl5{0, false, false, false, false, false, 0} << QVariant::fromValue<qint16>(0);
    QTest::newRow("RevSW 100") << IC_Ctrl5{0, false, false, false, false, false, 100} << QVariant::fromValue<qint16>(100);
    QTest::newRow("RevSW 1607") << IC_Ctrl5{0, false, false, false, false, false, 1607} << QVariant::fromValue<qint16>(1607);
}

void TestCanSignalBufferData::directionTestData()
{
    QTest::addColumn<IC_Ctrl7>("message");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Direction off") << IC_Ctrl7{Direction::OFF} << QVariant::fromValue<Direction>(Direction::OFF);
    QTest::newRow("Direction forward") << IC_Ctrl7{Direction::FORWARD} << QVariant::fromValue<Direction>(Direction::FORWARD);
    QTest::newRow("Direction reverse") << IC_Ctrl7{Direction::REVERSE} << QVariant::fromValue<Direction>(Direction::REVERSE);

}

void TestCanSignalBufferData::speedAverageTestData()
{
     QTest::addColumn<QVector<IC_Ctrl1>>("messages");
     QTest::addColumn<QVariant>("expected_value");

     QTest::newRow("Speed 1") << QVector<IC_Ctrl1>({IC_Ctrl1 {0, 0, 1252, VehicleMode::UNKNOWN},
                                                    IC_Ctrl1 {0, 0, 1351, VehicleMode::UNKNOWN},
                                                    IC_Ctrl1 {0, 0, 1256, VehicleMode::UNKNOWN}}) <<
                                 QVariant::fromValue<float>(calculate_moving_average( 1252, 1351, 1256) * 0.1);
}

void TestCanSignalBufferData::engineTempAverageTestData()
{
    QTest::addColumn<QVector<IC_Ctrl1>>("messages");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Temp 1") << QVector<IC_Ctrl1>({IC_Ctrl1 {0, 24, 0, VehicleMode::UNKNOWN},
                                                   IC_Ctrl1 {0, 36, 0, VehicleMode::UNKNOWN},
                                                   IC_Ctrl1 {0, 55, 0, VehicleMode::UNKNOWN}}) <<
                               QVariant::fromValue<quint8>(((24 + 36 + 56) / 3));
}

void TestCanSignalBufferData::socAverageTestData()
{
    QTest::addColumn<QVector<IC_Ctrl1>>("messages");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Soc 1") << QVector<IC_Ctrl1>({IC_Ctrl1 {13, 0, 0, VehicleMode::UNKNOWN},
                                                   IC_Ctrl1 {88, 0, 0, VehicleMode::UNKNOWN},
                                                   IC_Ctrl1 {56, 0, 0, VehicleMode::UNKNOWN}}) <<
                                QVariant::fromValue<float>(calculate_moving_average(13, 88, 56) * 0.5);
}

void TestCanSignalBufferData::limitHeatersAverageTestData()
{
    QTest::addColumn<QVector<IC_Ctrl5>>("messages");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Limit heaters 1") << QVector<IC_Ctrl5>({IC_Ctrl5 {25, false, false, false, false, false, 0},
                                                   IC_Ctrl5 {34, false, false, false, false, false, 0},
                                                   IC_Ctrl5 {22, false, false, false, false, false, 0}}) <<
                                QVariant::fromValue<qint16>(((25 + 34  + 22) / 3));
}

void TestCanSignalBufferData::revSWAverageTestData()
{
    QTest::addColumn<QVector<IC_Ctrl5>>("messages");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("revSW 1") << QVector<IC_Ctrl5>({IC_Ctrl5 {0, false, false, false, false, false, 13},
                                                   IC_Ctrl5 {0, false, false, false, false, false, 22},
                                                   IC_Ctrl5 {0, false, false, false, false, false, 19}}) <<
                                QVariant::fromValue<qint16>(((13 + 22 + 19) / 3));
}

void TestCanSignalBufferData::voltageAverageTestData()
{
    QTest::addColumn<QVector<BMS_INFO1>>("messages");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Voltage 1") << QVector<BMS_INFO1>({BMS_INFO1 {0, 13},
                                                   BMS_INFO1 {0, 22},
                                                   BMS_INFO1 {0, 19}}) <<
                                QVariant::fromValue<float>(calculate_moving_average(13, 22, 19) * 0.1);
}

void TestCanSignalBufferData::currentAverageTestData()
{
    QTest::addColumn<QVector<BMS_INFO1>>("messages");
    QTest::addColumn<QVariant>("expected_value");

    QTest::newRow("Current 1") << QVector<BMS_INFO1>({BMS_INFO1 {13, 0},
                                                   BMS_INFO1 {22, 0},
                                                   BMS_INFO1 {19, 0}}) <<
                                  QVariant::fromValue<float>((((13 + 22 + 19) / 3) * 0.1) - 1000);
}

float TestCanSignalBufferData::calculate_moving_average(int value1, int value2, int value3)
{
    float average = 0;
    int n = 0;
    n++;
    average = average + (value1 - average) / n;

    n++;
    average = average + (value2 - average) / n;

    n++;
    average = average + (value3 - average) / n;

    return average;
}

