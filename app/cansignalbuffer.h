#ifndef CANSIGNALBUFFER_H
#define CANSIGNALBUFFER_H

#include <forward_list>

#include <QObject>
#include <QTimer>
#include <QElapsedTimer>


#include <QtCharts/QLineSeries>

#include "canmessages.h"
#include "movingaverageaccumulator.h"
#include "chargingtimeestimator.h"

class CanSignalBuffer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QtCharts::QLineSeries* powerSeries READ powerSeries WRITE setPowerSeries NOTIFY powerSeriesChanged)
    Q_PROPERTY(QtCharts::QLineSeries* consumptionSeries READ consumptionSeries WRITE setConsumptionSeries NOTIFY consumptionSeriesChanged)
public:
    CanSignalBuffer(QObject *parent = nullptr);

    ChargingTimeEstimator getEstimator();

public slots:
    void receiveBMS_INFO1Message(BMS_INFO1 message);
    void receiveIC_Ctrl1Message(IC_Ctrl1 message);
    void receiveIC_Ctrl2Message(IC_Ctrl2 message);
    void receiveIC_Ctrl3Message(IC_Ctrl3 message);
    void receiveIC_Ctrl5Message(IC_Ctrl5 message);
    void receiveIC_Ctrl6Message(IC_Ctrl6 message);
    void receiveIC_Ctrl7Message(IC_Ctrl7 message);

    void updatePowerHistory();
    void updateConsumptionHistory();

    QtCharts::QLineSeries* powerSeries() const
    {
        return _powerSeries;
    }

    void setPowerSeries(QtCharts::QLineSeries* xy)
    {
        if(_powerSeries == xy) return;
        if(_powerSeries && _powerSeries->parent() == this)
                delete _powerSeries;
        _powerSeries = xy;
        emit powerSeriesChanged(_powerSeries);
    }

    QtCharts::QLineSeries* consumptionSeries() const
    {
        return _consumptionSeries;
    }
    void setConsumptionSeries(QtCharts::QLineSeries* xy)
    {
        if(_consumptionSeries == xy) return;
        if(_consumptionSeries && _consumptionSeries->parent() == this)
                delete _consumptionSeries;
        _consumptionSeries = xy;
        emit consumptionSeriesChanged(_consumptionSeries);
    }

signals:
    // BMS_INFO1
    void current(float current);
    void voltage(float voltage);
    // IC_Ctrl1
    void soc(float soc);
    void engineTemp(quint8 engineTemp);
    void speed(float speed);
    void vehicleMode(VehicleMode vehicleMode);
    // IC_Ctrl2
    // Timer
    // Brake
    void sportFlash(bool on);
    void standardFlash(bool on);
    void ecoFlash(bool on);
    void sportLit(bool on);
    void standardLit(bool on);
    void ecoLit(bool on);
    // IC_Ctrl3
    void odometer(double odometer);
    // Current limit
    // IC_Ctrl5
    // limitHeaters should actually be qint8, but it's working strangely with QML signals
    void limitHeaters(qint16 limitHeaters);
    void keyInserted(bool on);
    void lockChargingPort(bool on);
    void unlockChargingPort(bool on);
    void fcContactor(bool on);
    void acRequest(bool on);
    void revSW(qint16 revSW);
    // IC_Ctrl6
    void batLow(bool on);
    void batHigh(bool on);
    void checkEngine(bool on);
    void engineOverheat(bool on);
    void oil(bool on);
    void xBeep(bool on);
    void revLimit(bool on);
    void warmup(bool on);
    void ecm(bool on);
    void revFault(bool on);
    void drownMode(bool on);
    void throttleOpen(bool on);
    void noOil(bool on);
    void overheat(bool on);
    void knock(bool on);
    void throttleOpen2(bool on);
    void visualShutdown(bool on);
    void visualShutdownHold(bool on);
    void checkKey(bool on);
    void accel(bool on);
    void badKey(bool on);
    void shutdown(bool on);
    // IC_Ctrl7
    void direction(Direction direction);
    // Composed signals
    void power(double power);
    void powerSeriesChanged(QtCharts::QLineSeries*);
    void consumptionSeriesChanged(QtCharts::QLineSeries*);
    void consumptionChanged(float consumption);
    // Forwarded signals
    void chargingTimeEstimate(qint16 estimate);
    void chargingTimeElapsed(quint32 elapsed);

private:
    enum class BooleanSignal {
        // IC_Ctrl2
        SPORT_FLASH = 0,
        STANDARD_FLASH, ECO_FLASH, SPORT_LIT, STANDARD_LIT, ECO_LIT,
        // IC_Ctrl5
        KEY_INSERTED, LOCK_CHARGING_PORT, UNLOCK_CHARGING_PORT, FC_CONTACTOR, AC_REQUEST,
        // IC_Ctrl6
        BAT_LOW, BAT_HIGH, CHECK_ENGINE, ENGINE_OVERHEAT, OIL, X_BEEP, REV_LIMIT,
        WARMUP, ECM, REV_FAULT, DROWN_MODE, THROTTLE_OPEN, NO_OIL,
        OVERHEAT, KNOCK, THROTTLE_OPEN2, VISUAL_SHUTDOWN, VISUAL_SHUTDOWN_HOLD,
        CHECK_KEY, ACCEL, BAD_KEY, SHUTDOWN,
        BOOLEAN_SIGNAL_COUNT
    };
    QTimer refresh_;
    QTimer refreshPowerGraph_;
    QTimer refreshConsumptionGraph_;
    bool signalStatuses_[static_cast<int>(BooleanSignal::BOOLEAN_SIGNAL_COUNT)] = {false};

    MovingAverageAccumulator<quint8, float> socAccumulator_, engineTempAccumulator_, limitHeatersAccumulator_;
    MovingAverageAccumulator<quint16, float> speedAccumulator_, revSWAccumulator_, currentAccumulator_, voltageAccumulator_;
    MovingAverageAccumulator<double, float> powerGraphAccumulator_;
    MovingAverageAccumulator<double, float> distanceAccumulator_;
    MovingAverageAccumulator<double, float> powerConsumptionAccumulator_;
    MovingAverageAccumulator<double, float> speedConsumptionAccumulator_;

    ChargingTimeEstimator chargingTimeEstimator_;
    // Amount of power paired with the time when the power was meassured. Used for calculating power
    std::list<std::pair<float,qint64>> powerHistory_;
    QtCharts::QLineSeries* _powerSeries;
    
    std::list<std::pair<float,qint64>> consumptionHistory_;
    QtCharts::QLineSeries* _consumptionSeries;
    
    void emitIfNotChanged(bool signalValue, BooleanSignal signalName, void (CanSignalBuffer::*signal)(bool));

private slots:
    void emitAverages();
};

#endif // CANSIGNALBUFFER_H
