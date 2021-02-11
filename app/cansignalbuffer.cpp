#include "cansignalbuffer.h"

#include <QDateTime>
#include <QRandomGenerator>
#include <cmath>
#include "configuration.h"

CanSignalBuffer::CanSignalBuffer(QObject *parent) : QObject(parent), _powerSeries(nullptr), _consumptionSeries(nullptr)
{
    connect(&refresh_, &QTimer::timeout, this, &CanSignalBuffer::emitAverages);
    connect(&refreshPowerGraph_, &QTimer::timeout, this, &CanSignalBuffer::updatePowerHistory);
    connect(&refreshConsumptionGraph_,&QTimer::timeout, this, &CanSignalBuffer::updateConsumptionHistory);
    connect(this, &CanSignalBuffer::power, &chargingTimeEstimator_, &ChargingTimeEstimator::power);
    connect(this, &CanSignalBuffer::soc, &chargingTimeEstimator_, &ChargingTimeEstimator::soc);
    connect(&chargingTimeEstimator_, &ChargingTimeEstimator::timeEstimate, this, &CanSignalBuffer::chargingTimeEstimate);
    connect(&chargingTimeEstimator_, &ChargingTimeEstimator::timeElapsed, this, &CanSignalBuffer::chargingTimeElapsed);
    refresh_.setSingleShot(false);
    refresh_.start(Configuration::getInstance()->COMMON_AVERAGING_RATE);

    refreshConsumptionGraph_.setSingleShot(false);
    refreshConsumptionGraph_.start(Configuration::getInstance()->CONSUMPTION_AVERAGING_RATE);

    refreshPowerGraph_.setSingleShot(false);
    refreshPowerGraph_.start(Configuration::getInstance()->POWER_GRAPH_AVERAGING_RATE);
    chargingTimeEstimator_.batteryCapacity(Configuration::getInstance()->BATTERY_CAPACITY);
}

void CanSignalBuffer::receiveBMS_INFO1Message(BMS_INFO1 message)
{
    currentAccumulator_.accumulate(message.current);
    voltageAccumulator_.accumulate(message.voltage);
    float power = abs((message.voltage * 0.1) * ((currentAccumulator_.getAverage() * 0.1) - 1000));
    powerGraphAccumulator_.accumulate(power);
    powerConsumptionAccumulator_.accumulate(power);
}

void CanSignalBuffer::receiveIC_Ctrl1Message(IC_Ctrl1 message)
{
    static VehicleMode lastVehicleMode = VehicleMode::UNKNOWN;
    socAccumulator_.accumulate(message.soc);
    engineTempAccumulator_.accumulate(message.engineTemp);
    speedAccumulator_.accumulate(message.speed);
    speedConsumptionAccumulator_.accumulate(message.speed);


    if (message.vehicleMode != VehicleMode::UNKNOWN && message.vehicleMode != lastVehicleMode) {
        if (message.vehicleMode == VehicleMode::CHARGE) {
            chargingTimeEstimator_.chargingStarted();
        }
        else if (lastVehicleMode == VehicleMode::CHARGE){
            chargingTimeEstimator_.chargingEnded();
        }
        lastVehicleMode = message.vehicleMode;
        emit vehicleMode(message.vehicleMode);
    }
}

void CanSignalBuffer::receiveIC_Ctrl2Message(IC_Ctrl2 message)
{
    emitIfNotChanged(message.sportFlash, BooleanSignal::SPORT_FLASH, &CanSignalBuffer::sportFlash);
    emitIfNotChanged(message.standardFlash, BooleanSignal::STANDARD_FLASH, &CanSignalBuffer::standardFlash);
    emitIfNotChanged(message.ecoFlash, BooleanSignal::ECO_FLASH, &CanSignalBuffer::ecoFlash);
    emitIfNotChanged(message.sportLit, BooleanSignal::SPORT_LIT, &CanSignalBuffer::sportLit);
    emitIfNotChanged(message.standardLit, BooleanSignal::STANDARD_LIT, &CanSignalBuffer::standardLit);
    emitIfNotChanged(message.ecoLit, BooleanSignal::ECO_LIT, &CanSignalBuffer::ecoLit);
}

void CanSignalBuffer::receiveIC_Ctrl3Message(IC_Ctrl3 message)
{
    static quint32 odometerLastValue = 0;
    if (odometerLastValue != message.odometer) {
        emit odometer(message.odometer * 0.1);
        odometerLastValue = message.odometer;
    }
}

void CanSignalBuffer::receiveIC_Ctrl5Message(IC_Ctrl5 message)
{
    limitHeatersAccumulator_.accumulate(message.limitHeaters);
    emitIfNotChanged(message.keyInserted, BooleanSignal::KEY_INSERTED, &CanSignalBuffer::keyInserted);
    emitIfNotChanged(message.lockChargingPort, BooleanSignal::LOCK_CHARGING_PORT, &CanSignalBuffer::lockChargingPort);
    emitIfNotChanged(message.unlockChargingPort, BooleanSignal::UNLOCK_CHARGING_PORT, &CanSignalBuffer::unlockChargingPort);
    emitIfNotChanged(message.fcContactor, BooleanSignal::FC_CONTACTOR, &CanSignalBuffer::fcContactor);
    emitIfNotChanged(message.acRequest, BooleanSignal::AC_REQUEST, &CanSignalBuffer::acRequest);
    revSWAccumulator_.accumulate(message.revSW);
}

void CanSignalBuffer::receiveIC_Ctrl6Message(IC_Ctrl6 message)
{
    emitIfNotChanged(message.batLow, BooleanSignal::BAT_LOW, &CanSignalBuffer::batLow);
    emitIfNotChanged(message.batHigh, BooleanSignal::BAT_HIGH, &CanSignalBuffer::batHigh);
    emitIfNotChanged(message.checkEngine, BooleanSignal::CHECK_ENGINE, &CanSignalBuffer::checkEngine);
    emitIfNotChanged(message.engineOverheat, BooleanSignal::ENGINE_OVERHEAT, &CanSignalBuffer::engineOverheat);
    emitIfNotChanged(message.oil, BooleanSignal::OIL, &CanSignalBuffer::oil);
    emitIfNotChanged(message.xBeep, BooleanSignal::X_BEEP, &CanSignalBuffer::xBeep);
    emitIfNotChanged(message.revLimit, BooleanSignal::REV_LIMIT, &CanSignalBuffer::revLimit);
    emitIfNotChanged(message.warmup, BooleanSignal::WARMUP, &CanSignalBuffer::warmup);
    emitIfNotChanged(message.ecm, BooleanSignal::ECM, &CanSignalBuffer::ecm);
    emitIfNotChanged(message.revFault, BooleanSignal::REV_FAULT, &CanSignalBuffer::revFault);
    emitIfNotChanged(message.drownMode, BooleanSignal::DROWN_MODE, &CanSignalBuffer::drownMode);
    emitIfNotChanged(message.throttleOpen, BooleanSignal::THROTTLE_OPEN, &CanSignalBuffer::throttleOpen);
    emitIfNotChanged(message.noOil, BooleanSignal::NO_OIL, &CanSignalBuffer::noOil);
    emitIfNotChanged(message.overheat, BooleanSignal::OVERHEAT, &CanSignalBuffer::overheat);
    emitIfNotChanged(message.knock, BooleanSignal::KNOCK, &CanSignalBuffer::knock);
    emitIfNotChanged(message.throttleOpen2, BooleanSignal::THROTTLE_OPEN2, &CanSignalBuffer::throttleOpen2);
    emitIfNotChanged(message.visualShutdown, BooleanSignal::VISUAL_SHUTDOWN, &CanSignalBuffer::visualShutdown);
    emitIfNotChanged(message.visualShutdownHold, BooleanSignal::VISUAL_SHUTDOWN_HOLD, &CanSignalBuffer::visualShutdownHold);
    emitIfNotChanged(message.checkKey, BooleanSignal::CHECK_KEY, &CanSignalBuffer::checkKey);
    emitIfNotChanged(message.accel, BooleanSignal::ACCEL, &CanSignalBuffer::accel);
    emitIfNotChanged(message.badKey, BooleanSignal::BAD_KEY, &CanSignalBuffer::badKey);
    emitIfNotChanged(message.shutdown, BooleanSignal::SHUTDOWN, &CanSignalBuffer::shutdown);
}

void CanSignalBuffer::receiveIC_Ctrl7Message(IC_Ctrl7 message)
{
    static Direction lastDirection = Direction::UNKNOWN;
    if (message.direction != Direction::UNKNOWN && message.direction != lastDirection) {
        lastDirection = message.direction;
        emit direction(message.direction);
    }
}

void CanSignalBuffer::updatePowerHistory()
{
    auto d = powerGraphAccumulator_.reset();
    powerHistory_.push_front({d, Configuration::getInstance()->POWER_GRAPH_AVERAGING_RATE});
    if (!_powerSeries || powerHistory_.empty()) {
        return;
    }
    QVector<QPointF> powerHistory;
    auto timeCounter = 0;

    // Add power history here
    for (auto power : powerHistory_) {
        timeCounter -= power.second;
        powerHistory.push_back(
                    QPointF(timeCounter,
                            power.first));
    }

    if (timeCounter - powerHistory_.back().second > 10000) {
        powerHistory_.pop_back();
    }

    _powerSeries->replace(powerHistory);
    emit powerSeriesChanged(_powerSeries);
}

void CanSignalBuffer::updateConsumptionHistory()
{
    float d = 0;
    if(powerConsumptionAccumulator_.hasValue() && speedConsumptionAccumulator_.hasValue()){
        float speed = speedConsumptionAccumulator_.reset();
        if(std::abs(speed) >= 1){
            float power = powerConsumptionAccumulator_.reset();
            d = power / speed;
        }
    }
    emit consumptionChanged(d);
    consumptionHistory_.push_front({d, Configuration::getInstance()->CONSUMPTION_AVERAGING_RATE});

    if(!_consumptionSeries || consumptionHistory_.empty()){
        return;
    }

    QVector<QPointF> consumptionHistory;
    auto timeCounter = 0;

    for (auto consumption : consumptionHistory_){
        timeCounter -= consumption.second;
        consumptionHistory.push_back(
                        QPointF(timeCounter, consumption.first));
    }
    if (timeCounter - consumptionHistory_.back().second > 10000){
        consumptionHistory_.pop_back();
    }
    _consumptionSeries->replace(consumptionHistory);
    emit consumptionSeriesChanged(_consumptionSeries);
}


void CanSignalBuffer::emitAverages()
{
    if (speedAccumulator_.hasValue()) {
        emit speed(speedAccumulator_.reset() * 0.1);
    }
    if (engineTempAccumulator_.hasValue()) {
        emit engineTemp(engineTempAccumulator_.reset() / 10);
    }
    if (socAccumulator_.hasValue()) {
        emit soc(socAccumulator_.reset() * 0.5);
    }

    if (limitHeatersAccumulator_.hasValue()) {
        emit limitHeaters(qRound64(limitHeatersAccumulator_.reset()));
    }

    if (revSWAccumulator_.hasValue()) {
        emit revSW(qRound64(revSWAccumulator_.reset()));
    }
    float averageCurrent, averageVoltage;
    if (currentAccumulator_.hasValue()) {
        averageCurrent = (currentAccumulator_.getAverage() * 0.1) - 1000;
        emit current(averageCurrent);
    }
    if (voltageAccumulator_.hasValue()) {
        averageVoltage = voltageAccumulator_.getAverage() * 0.1;
        emit voltage(averageVoltage);
    }

    if (currentAccumulator_.hasValue() && voltageAccumulator_.hasValue()) {
        auto powerValue = abs(averageCurrent * averageVoltage);
        emit power(powerValue);        
    }
    currentAccumulator_.reset();
    voltageAccumulator_.reset();
}

void CanSignalBuffer::emitIfNotChanged(bool signalValue, BooleanSignal signalName, void (CanSignalBuffer::*signal)(bool))
{
    if (signalValue != signalStatuses_[static_cast<int>(signalName)]) {
        signalStatuses_[static_cast<int>(signalName)] = signalValue;
        emit (this->*signal)(signalValue);
    }
}
