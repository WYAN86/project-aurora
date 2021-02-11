#include "chargingtimeestimator.h"

#include <QDateTime>
#include <configuration.h>

ChargingTimeEstimator::ChargingTimeEstimator(QObject *parent) : QObject(parent)
{
    refresh_.setSingleShot(false);
    connect(&refresh_, &QTimer::timeout, this, &ChargingTimeEstimator::createEstimate);
}

void ChargingTimeEstimator::soc(float soc)
{
    if (state_ == EstimatorState::WAITING_SOC) {
        remainingEnergy_ = batteryCapacity_ *  3600 * ((Configuration::getInstance()->SOC_ON_BULK_CHARGE_END - soc) / 100);
        state_ = EstimatorState::RUNNING;
        refresh_.start(Configuration::getInstance()->CHARGING_TIME_REFRESH_RATE);
        msecsSinceEpochOnLastUpdate_ = QDateTime::currentMSecsSinceEpoch();
    }
}

void ChargingTimeEstimator::power(double power)
{
    if (state_ == EstimatorState::RUNNING) {
        powerAccumulator_.accumulate(power);
    }
}

void ChargingTimeEstimator::chargingStarted()
{
    emit timeEstimate(-1);
    emit timeElapsed(0);
    state_ = EstimatorState::WAITING_SOC;
    msecsSinceCharginStarted_ = QDateTime::currentMSecsSinceEpoch();
}

void ChargingTimeEstimator::chargingEnded()
{
    refresh_.stop();
    remainingEnergy_ = 0;
    msecsSinceCharginStarted_ = 0;
    state_ = EstimatorState::IDLE;
}

void ChargingTimeEstimator::batteryCapacity(quint16 capacity)
{
    batteryCapacity_ = capacity;
}

void ChargingTimeEstimator::createEstimate()
{
    quint64 msecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();
    double averagePower = powerAccumulator_.reset();
    quint64 timeDiff = msecsSinceEpoch - msecsSinceEpochOnLastUpdate_;
    double averageEnergy = averagePower * timeDiff / 1000;
    remainingEnergy_ -= averageEnergy;
    quint16 remainingTime = qRound(remainingEnergy_ / averagePower);
    msecsSinceEpochOnLastUpdate_ = msecsSinceEpoch;
    quint64 elapsedTime = msecsSinceEpoch - msecsSinceCharginStarted_;
    emit timeEstimate(remainingTime);
    emit timeElapsed(elapsedTime);
}
