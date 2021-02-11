#ifndef CHARGINGTIMEESTIMATOR_H
#define CHARGINGTIMEESTIMATOR_H

#include "movingaverageaccumulator.h"

#include <QObject>
#include <QTimer>

class ChargingTimeEstimator : public QObject
{
    Q_OBJECT
public:
    ChargingTimeEstimator(QObject *parent = nullptr);
public slots:
    void soc(float soc);
    void power(double power);
    void chargingStarted();
    void chargingEnded();
    /**
     * @brief Sets the battery capacity that is considered as full charge. Takes effect
     * when chargingStarted is called next time.
     * @param capacity Battery capacity in Wh
     */
    void batteryCapacity(quint16 capacity);

signals:
    /**
     * @brief Triggers when new estimate of remaining charging time is available.
     * @param timeEstimate Estimated time in seconds that is left to full battery. Value is negative is estimate cannot be given.
     */
    void timeEstimate(qint32 timeEstimate);

    /**
     * @brief timeElapsed Trigges whenever the estimates update.
     * @param timeElapsed time elapsed from when the chraging started
     */

    void timeElapsed(quint64 timeElapsed);

private:
    enum class EstimatorState {
        IDLE, WAITING_SOC, RUNNING
    };
    EstimatorState state_ = EstimatorState::IDLE;
    /**
     * @brief Energy that is still needed to feed to the battery.
     * Unit is J (= Ws = Wh * 3600).
     */
    quint32 remainingEnergy_;
    quint16 batteryCapacity_;
    quint64 msecsSinceEpochOnLastUpdate_;

    quint64 msecsSinceCharginStarted_;

    MovingAverageAccumulator<double, double>  powerAccumulator_;
    QTimer refresh_;

private slots:
    void createEstimate();
};

#endif // CHARGINGTIMEESTIMATOR_H
