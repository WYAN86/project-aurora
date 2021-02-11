#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QSettings>
#include <exception>

class Configuration : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint8 POWER_DECIMAL_PLACES MEMBER POWER_DECIMAL_PLACES CONSTANT)
public:
    /**
     * @brief Device file name of the CAN bus
     */
    const QString CAN_BUS_NAME;
    /**
     * @brief Timeout in milliseconds after which a timeout exception should be sent if no can messages received
     */
    const quint16 CAN_BUS_TIMEOUT;
    /**
     * @brief Battery capacity in Wh
     */
    const quint16 BATTERY_CAPACITY;
    /**
     * @brief Number of decimals that should be shown for power value
     */
    const quint8 POWER_DECIMAL_PLACES;
    /**
     * @brief Consumption maximum value in Wh
     */
    const quint16 CONSUMPTION_MAXIMUM;
    /**
     * @brief Regeneration maximum in Wh
     */
    const quint16 REGENERATION_MAXIMUM;
    /**
     * @brief Rate on which average calculation for consumption should be done. Unit is milliseconds
     */
    const quint16 CONSUMPTION_AVERAGING_RATE;
    /**
     * @brief Rate on which average calculation for power graph should be done. Unit is milliseconds
     */
    const quint16 POWER_GRAPH_AVERAGING_RATE;
    /**
     * @brief Rate in which charging time estimate should be updated
     */
    const quint16 CHARGING_TIME_REFRESH_RATE;
    /**
     * @brief SOC value when bulk charge state ends
     */
    const quint8 SOC_ON_BULK_CHARGE_END;
    /**
     * @brief Rate on which average calculation should be done. Unit is milliseconds
     */
    const quint16 COMMON_AVERAGING_RATE;

    static Configuration* getInstance();

public slots:
    QString configToString();
private:
    static constexpr const char* CONFIGURATION_FILE_LOCATION = "config/config.ini";
    static Configuration* instance;
    Configuration(QSettings& qsettings, QObject *parent = nullptr);
    QVariant getValueOrThrow(QSettings& qsettings, QString key);
    template<typename T>
    T getIntegerValueOrThrow(QSettings& qsettings, QString key);
};

class ConfigurationException : public std::exception
{
public:
    enum class ErrorType {
        MISSING_CONFIGURATION_FILE, MISSING_CONFIGURATION_ITEM, INVALID_CONFIGURATION_VALUE_TYPE, CONFIGURATION_ITEM_OUT_OF_RANGE
    };
    ConfigurationException(ErrorType type, QString details);
private:
    const ErrorType type_;
    const QString details_;
};

#endif // CONFIGURATION_H
