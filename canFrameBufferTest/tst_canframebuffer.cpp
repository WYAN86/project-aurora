#include <QtTest>
#include <QTest>
#include <QSignalSpy>
#include <iostream>

#include "cansignalbuffer.h"
#include "canmessages.h"
#include "canframebuffer_test_data.cpp"

// add necessary includes here

class TestCanSignalBuffer : public QObject
{
    Q_OBJECT

public:
    TestCanSignalBuffer();
    ~TestCanSignalBuffer();

private:
    CanSignalBuffer* buffer_ = nullptr;

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_current_signal_data();
    void test_current_signal();

    void test_voltage_signal_data();
    void test_voltage_signal();

    void test_power_signal_data();
    void test_power_signal();

    void test_soc_signal_data();
    void test_soc_signal();

    void test_engineTemp_signal_data();
    void test_engineTemp_signal();

    void test_speed_signal_data();
    void test_speed_signal();

    void test_vehicle_mode_signal_data();
    void test_vehicle_mode_signal();

    void test_sport_flash_signal_data();
    void test_sport_flash_signal();

    void test_standard_flash_signal_data();
    void test_standard_flash_signal();

    void test_eco_flash_signal_data();
    void test_eco_flash_signal();

    void test_sport_lit_signal_data();
    void test_sport_lit_signal();

    void test_standard_lit_signal_data();
    void test_standard_lit_signal();

    void test_eco_lit_signal_data();
    void test_eco_lit_signal();

    void test_odometer_signal_data();
    void test_odometer_signal();

    void test_limit_heaters_signal_data();
    void test_limit_heaters_signal();

    void test_key_inserted_signal_data();
    void test_key_inserted_signal();

    void test_lock_port_signal_data();
    void test_lock_port_signal();

    void test_unlock_port_signal_data();
    void test_unlock_port_signal();

    void test_fc_contactor_signal_data();
    void test_fc_contactor_signal();

    void test_ac_request_signal_data();
    void test_ac_request_signal();

    void test_revSW_signal_data();
    void test_revSW_signal();

    void test_direction_signal_data();
    void test_direction_signal();

    void test_power_history_signal();

    void test_speed_average_data();
    void test_speed_average();

    void test_engine_temp_average_data();
    void test_engine_temp_average();

    void test_soc_average_data();
    void test_soc_average();

    void test_heaters_average_data();
    void test_heaters_average();

    void test_revSW_average_data();
    void test_revSW_average();

    void test_voltage_average_data();
    void test_voltage_average();

    void test_current_average_data();
    void test_current_average();

};

TestCanSignalBuffer::TestCanSignalBuffer()
{

}

TestCanSignalBuffer::~TestCanSignalBuffer()
{

}

void TestCanSignalBuffer::initTestCase()
{
    buffer_ = new CanSignalBuffer();
}

void TestCanSignalBuffer::cleanupTestCase()
{
    delete buffer_;
}

// Current
void TestCanSignalBuffer::test_current_signal_data()
{
    TestCanSignalBufferData::currentTestData();
}

void TestCanSignalBuffer::test_current_signal()
{
    QFETCH(BMS_INFO1, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_current(buffer_, SIGNAL(current(float)));

    buffer_->receiveBMS_INFO1Message(message);

    QVERIFY(spy_current.wait(150));

    QCOMPARE(spy_current.first().at(0), expected_value);
}

// Voltage
void TestCanSignalBuffer::test_voltage_signal_data()
{
    TestCanSignalBufferData::voltageTestData();
}

void TestCanSignalBuffer::test_voltage_signal()
{
    QFETCH(BMS_INFO1, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_voltage(buffer_, SIGNAL(voltage(float)));

    buffer_->receiveBMS_INFO1Message(message);

    QVERIFY(spy_voltage.wait(150));

    QCOMPARE(spy_voltage.first().at(0), expected_value);
}

void TestCanSignalBuffer::test_power_signal_data()
{
    TestCanSignalBufferData::powerTestData();
}

void TestCanSignalBuffer::test_power_signal()
{
    QFETCH(BMS_INFO1, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_power(buffer_, SIGNAL(power(double)));

    buffer_->receiveBMS_INFO1Message(message);

    QVERIFY(spy_power.wait(150));

    QCOMPARE(spy_power.first().at(0), expected_value);
}

// Soc
void TestCanSignalBuffer::test_soc_signal_data()
{
    TestCanSignalBufferData::socTestData();
}

void TestCanSignalBuffer::test_soc_signal()
{
    QFETCH(IC_Ctrl1, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_soc(buffer_, SIGNAL(soc(float)));

    buffer_->receiveIC_Ctrl1Message(message);

    QVERIFY(spy_soc.wait(150));

    QCOMPARE(spy_soc.first().at(0), expected_value);
}

// Engine Temp
void TestCanSignalBuffer::test_engineTemp_signal_data()
{
    TestCanSignalBufferData::engineTempTestData();
}

void TestCanSignalBuffer::test_engineTemp_signal()
{
    QFETCH(IC_Ctrl1, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_engineTemp(buffer_, SIGNAL(engineTemp(quint8)));

    buffer_->receiveIC_Ctrl1Message(message);

    QVERIFY(spy_engineTemp.wait(150));

    QCOMPARE(spy_engineTemp.first().at(0), expected_value);
}

// Speed
void TestCanSignalBuffer::test_speed_signal_data()
{
    TestCanSignalBufferData::speedTestData();
}

void TestCanSignalBuffer::test_speed_signal()
{
    QFETCH(IC_Ctrl1, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_speed(buffer_, SIGNAL(speed(float)));

    buffer_->receiveIC_Ctrl1Message(message);

    QVERIFY(spy_speed.wait(150));

    QCOMPARE(spy_speed.first().at(0), expected_value);
}



// Vehicle Mode
void TestCanSignalBuffer::test_vehicle_mode_signal_data()
{
    TestCanSignalBufferData::vehicleModeTestData();
}

void TestCanSignalBuffer::test_vehicle_mode_signal()
{
    QFETCH(IC_Ctrl1, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_vehicleMode(buffer_, SIGNAL(vehicleMode(VehicleMode)));

    buffer_->receiveIC_Ctrl1Message(message);

    QVERIFY(spy_vehicleMode.count() == 1);

    QCOMPARE(spy_vehicleMode.first().at(0), expected_value);

    spy_vehicleMode.clear();
    buffer_->receiveIC_Ctrl1Message(message);
    QCOMPARE(spy_vehicleMode.count(), 0);

}

// Sport flash
void TestCanSignalBuffer::test_sport_flash_signal_data()
{
    TestCanSignalBufferData::sportFlashTestData();
}

void TestCanSignalBuffer::test_sport_flash_signal()
{
    QFETCH(IC_Ctrl2, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_sportFlash(buffer_, SIGNAL(sportFlash(bool)));

    buffer_->receiveIC_Ctrl2Message(message);

    QVERIFY(spy_sportFlash.count() == 1);

    QCOMPARE(spy_sportFlash.first().at(0), expected_value);

    spy_sportFlash.clear();
    buffer_->receiveIC_Ctrl2Message(message);
    QCOMPARE(spy_sportFlash.count(), 0);
}

// Standard Flash
void TestCanSignalBuffer::test_standard_flash_signal_data()
{
    TestCanSignalBufferData::standardFlashTestData();
}

void TestCanSignalBuffer::test_standard_flash_signal()
{
    QFETCH(IC_Ctrl2, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_standardFlash(buffer_, SIGNAL(standardFlash(bool)));

    buffer_->receiveIC_Ctrl2Message(message);

    QVERIFY(spy_standardFlash.count() == 1);

    QCOMPARE(spy_standardFlash.first().at(0), expected_value);

    spy_standardFlash.clear();
    buffer_->receiveIC_Ctrl2Message(message);
    QCOMPARE(spy_standardFlash.count(), 0);
}

// Eco Flash
void TestCanSignalBuffer::test_eco_flash_signal_data()
{
    TestCanSignalBufferData::ecoFlashTestData();
}

void TestCanSignalBuffer::test_eco_flash_signal()
{
    QFETCH(IC_Ctrl2, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_ecoFlash(buffer_, SIGNAL(ecoFlash(bool)));

    buffer_->receiveIC_Ctrl2Message(message);

    QVERIFY(spy_ecoFlash.count() == 1);

    QCOMPARE(spy_ecoFlash.first().at(0), expected_value);

    spy_ecoFlash.clear();
    buffer_->receiveIC_Ctrl2Message(message);
    QCOMPARE(spy_ecoFlash.count(), 0);
}

// Sport lit
void TestCanSignalBuffer::test_sport_lit_signal_data()
{
    TestCanSignalBufferData::sportLitTestData();
}

void TestCanSignalBuffer::test_sport_lit_signal()
{
    QFETCH(IC_Ctrl2, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_sportLit(buffer_, SIGNAL(sportLit(bool)));

    buffer_->receiveIC_Ctrl2Message(message);

    QVERIFY(spy_sportLit.count() == 1);

    QCOMPARE(spy_sportLit.first().at(0), expected_value);

    spy_sportLit.clear();
    buffer_->receiveIC_Ctrl2Message(message);
    QCOMPARE(spy_sportLit.count(), 0);
}

//Standard lit
void TestCanSignalBuffer::test_standard_lit_signal_data()
{
    TestCanSignalBufferData::standardLitTestData();
}

void TestCanSignalBuffer::test_standard_lit_signal()
{
    QFETCH(IC_Ctrl2, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_standardLit(buffer_, SIGNAL(standardLit(bool)));

    buffer_->receiveIC_Ctrl2Message(message);

    QVERIFY(spy_standardLit.count() == 1);

    QCOMPARE(spy_standardLit.first().at(0), expected_value);

    spy_standardLit.clear();
    buffer_->receiveIC_Ctrl2Message(message);
    QCOMPARE(spy_standardLit.count(), 0);
}

// Eco lit
void TestCanSignalBuffer::test_eco_lit_signal_data()
{
    TestCanSignalBufferData::ecoLitTestData();
}

void TestCanSignalBuffer::test_eco_lit_signal()
{
    QFETCH(IC_Ctrl2, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_ecoLit(buffer_, SIGNAL(ecoLit(bool)));

    buffer_->receiveIC_Ctrl2Message(message);

    QVERIFY(spy_ecoLit.count() == 1);

    QCOMPARE(spy_ecoLit.first().at(0), expected_value);

    spy_ecoLit.clear();
    buffer_->receiveIC_Ctrl2Message(message);
    QCOMPARE(spy_ecoLit.count(), 0);
}

// Odometer
void TestCanSignalBuffer::test_odometer_signal_data()
{
    TestCanSignalBufferData::odometerTestData();
}

void TestCanSignalBuffer::test_odometer_signal()
{
    QFETCH(IC_Ctrl3, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(odometer(double)));

    buffer_->receiveIC_Ctrl3Message(message);

    QVERIFY(spy_signal.count() == 1);

    QCOMPARE(spy_signal.first().at(0), expected_value);

    spy_signal.clear();
    buffer_->receiveIC_Ctrl3Message(message);
    QCOMPARE(spy_signal.count(), 0);
}

// Limit heaters
void TestCanSignalBuffer::test_limit_heaters_signal_data()
{
    TestCanSignalBufferData::limitHeatersTestData();
}

void TestCanSignalBuffer::test_limit_heaters_signal()
{
    QFETCH(IC_Ctrl5, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(limitHeaters(qint16)));

    buffer_->receiveIC_Ctrl5Message(message);

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.first().at(0), expected_value);
}

// Key inserted
void TestCanSignalBuffer::test_key_inserted_signal_data()
{
    TestCanSignalBufferData::keyInsertedTestData();
}

void TestCanSignalBuffer::test_key_inserted_signal()
{
    QFETCH(IC_Ctrl5, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(keyInserted(bool)));

    buffer_->receiveIC_Ctrl5Message(message);

    QVERIFY(spy_signal.count() == 1);

    QCOMPARE(spy_signal.first().at(0), expected_value);

    spy_signal.clear();
    buffer_->receiveIC_Ctrl5Message(message);
    QCOMPARE(spy_signal.count(), 0);
}


// Lock port
void TestCanSignalBuffer::test_lock_port_signal_data()
{
    TestCanSignalBufferData::lockChargingPortTestData();
}

void TestCanSignalBuffer::test_lock_port_signal()
{
    QFETCH(IC_Ctrl5, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(lockChargingPort(bool)));

    buffer_->receiveIC_Ctrl5Message(message);

    QVERIFY(spy_signal.count() == 1);

    QCOMPARE(spy_signal.first().at(0), expected_value);

    spy_signal.clear();
    buffer_->receiveIC_Ctrl5Message(message);
    QCOMPARE(spy_signal.count(), 0);
}


// Unlock port
void TestCanSignalBuffer::test_unlock_port_signal_data()
{
    TestCanSignalBufferData::unlockChargingPortTestData();
}

void TestCanSignalBuffer::test_unlock_port_signal()
{
    QFETCH(IC_Ctrl5, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(unlockChargingPort(bool)));

    buffer_->receiveIC_Ctrl5Message(message);

    QVERIFY(spy_signal.count() == 1);

    QCOMPARE(spy_signal.first().at(0), expected_value);

    spy_signal.clear();
    buffer_->receiveIC_Ctrl5Message(message);
    QCOMPARE(spy_signal.count(), 0);
}


// Fc contactor
void TestCanSignalBuffer::test_fc_contactor_signal_data()
{
    TestCanSignalBufferData::fcContactorTestData();
}

void TestCanSignalBuffer::test_fc_contactor_signal()
{
    QFETCH(IC_Ctrl5, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(fcContactor(bool)));

    buffer_->receiveIC_Ctrl5Message(message);

    QVERIFY(spy_signal.count() == 1);

    QCOMPARE(spy_signal.first().at(0), expected_value);

    spy_signal.clear();
    buffer_->receiveIC_Ctrl5Message(message);
    QCOMPARE(spy_signal.count(), 0);
}

// Ac request
void TestCanSignalBuffer::test_ac_request_signal_data()
{
    TestCanSignalBufferData::acRequestTestData();
}

void TestCanSignalBuffer::test_ac_request_signal()
{
    QFETCH(IC_Ctrl5, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(acRequest(bool)));

    buffer_->receiveIC_Ctrl5Message(message);

    QVERIFY(spy_signal.count() == 1);

    QCOMPARE(spy_signal.first().at(0), expected_value);

    spy_signal.clear();
    buffer_->receiveIC_Ctrl5Message(message);
    QCOMPARE(spy_signal.count(), 0);
}

// RevSW
void TestCanSignalBuffer::test_revSW_signal_data()
{
    TestCanSignalBufferData::revSWTestData();
}

void TestCanSignalBuffer::test_revSW_signal()
{
    QFETCH(IC_Ctrl5, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(revSW(qint16)));

    buffer_->receiveIC_Ctrl5Message(message);

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.first().at(0), expected_value);
}

void TestCanSignalBuffer::test_direction_signal_data()
{
    TestCanSignalBufferData::directionTestData();
}

void TestCanSignalBuffer::test_direction_signal()
{
    QFETCH(IC_Ctrl7, message);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(direction(Direction)));

    buffer_->receiveIC_Ctrl7Message(message);

    QVERIFY(spy_signal.count() == 1);

    QCOMPARE(spy_signal.first().at(0), expected_value);

    spy_signal.clear();
    buffer_->receiveIC_Ctrl7Message(message);
    QCOMPARE(spy_signal.count(), 0);
}

// Just the signal
void TestCanSignalBuffer::test_power_history_signal()
{
    QSignalSpy spy_signal(buffer_, SIGNAL(powerSeriesChanged(QtCharts::QLineSeries*)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveBMS_INFO1Message(BMS_INFO1 {50, 50});
    spy_signal.wait();

}

void TestCanSignalBuffer::test_speed_average_data()
{
    TestCanSignalBufferData::speedAverageTestData();
}

void TestCanSignalBuffer::test_speed_average()
{
    QFETCH(QVector<IC_Ctrl1>, messages);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(speed(float)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveIC_Ctrl1Message(IC_Ctrl1 {0, 0, 0, VehicleMode::UNKNOWN});
    spy_signal.wait(150);

    //Send the real data messages
    for(auto message: messages) {
        buffer_->receiveIC_Ctrl1Message(message);
    }

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.at(1).at(0), expected_value);
}

void TestCanSignalBuffer::test_engine_temp_average_data()
{
    TestCanSignalBufferData::engineTempAverageTestData();
}

void TestCanSignalBuffer::test_engine_temp_average()
{
    QFETCH(QVector<IC_Ctrl1>, messages);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(engineTemp(quint8)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveIC_Ctrl1Message(IC_Ctrl1 {0, 0, 0, VehicleMode::UNKNOWN});
    spy_signal.wait(150);

    //Send the real data messages
    for(auto message: messages) {
        buffer_->receiveIC_Ctrl1Message(message);
    }

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.at(1).at(0), expected_value);
}

void TestCanSignalBuffer::test_soc_average_data()
{
    TestCanSignalBufferData::socAverageTestData();
}

void TestCanSignalBuffer::test_soc_average()
{
    QFETCH(QVector<IC_Ctrl1>, messages);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(soc(float)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveIC_Ctrl1Message(IC_Ctrl1 {0, 0, 0, VehicleMode::UNKNOWN});
    spy_signal.wait(150);

    //Send the real data messages
    for(auto message: messages) {
        buffer_->receiveIC_Ctrl1Message(message);
    }

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.at(1).at(0), expected_value);
}

void TestCanSignalBuffer::test_heaters_average_data()
{
    TestCanSignalBufferData::limitHeatersAverageTestData();
}

void TestCanSignalBuffer::test_heaters_average()
{
    QFETCH(QVector<IC_Ctrl5>, messages);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(limitHeaters(qint16)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveIC_Ctrl5Message(IC_Ctrl5 {0, false, false, false, false, false, 0});
    spy_signal.wait(150);

    //Send the real data messages
    for(auto message: messages) {
        buffer_->receiveIC_Ctrl5Message(message);
    }

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.at(1).at(0), expected_value);
}

void TestCanSignalBuffer::test_revSW_average_data()
{
    TestCanSignalBufferData::revSWAverageTestData();
}

void TestCanSignalBuffer::test_revSW_average()
{
    QFETCH(QVector<IC_Ctrl5>, messages);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(revSW(qint16)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveIC_Ctrl5Message(IC_Ctrl5 {0, false, false, false, false, false, 0});
    spy_signal.wait(150);

    //Send the real data messages
    for(auto message: messages) {
        buffer_->receiveIC_Ctrl5Message(message);
    }

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.at(1).at(0), expected_value);
}

void TestCanSignalBuffer::test_voltage_average_data()
{
    TestCanSignalBufferData::voltageAverageTestData();
}

void TestCanSignalBuffer::test_voltage_average()
{
    QFETCH(QVector<BMS_INFO1>, messages);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(voltage(float)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveBMS_INFO1Message(BMS_INFO1 {0, 0});
    spy_signal.wait(150);

    //Send the real data messages
    for(auto message: messages) {
        buffer_->receiveBMS_INFO1Message(message);
    }

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.at(1).at(0), expected_value);
}

void TestCanSignalBuffer::test_current_average_data()
{
    TestCanSignalBufferData::currentAverageTestData();
}

void TestCanSignalBuffer::test_current_average()
{
    QFETCH(QVector<BMS_INFO1>, messages);
    QFETCH(QVariant, expected_value);
    QSignalSpy spy_signal(buffer_, SIGNAL(current(float)));

    //Send extra empty message to see when the averages are emited.
    buffer_->receiveBMS_INFO1Message(BMS_INFO1 {0, 0});
    spy_signal.wait(150);

    //Send the real data messages
    for(auto message: messages) {
        buffer_->receiveBMS_INFO1Message(message);
    }

    QVERIFY(spy_signal.wait(150));

    QCOMPARE(spy_signal.at(1).at(0), expected_value);
}





QTEST_GUILESS_MAIN(TestCanSignalBuffer)

#include "tst_canframebuffer.moc"
