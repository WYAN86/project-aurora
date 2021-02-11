#include "configuration.h"

#include <QString>
#include <QFileInfo>

Configuration* Configuration::instance = 0;

Configuration::Configuration(QSettings& qsettings, QObject *parent) :
    QObject(parent),
    CAN_BUS_NAME(getValueOrThrow(qsettings, "can_bus_name").toString()),
    CAN_BUS_TIMEOUT(getIntegerValueOrThrow<quint16>(qsettings, "can_timeout")),
    BATTERY_CAPACITY(getIntegerValueOrThrow<quint16>(qsettings, "battery_capacity")),
    POWER_DECIMAL_PLACES(getIntegerValueOrThrow<quint8>(qsettings, "power_decimal_places")),
    CONSUMPTION_MAXIMUM(getIntegerValueOrThrow<quint16>(qsettings, "consumption_maximum")),
    REGENERATION_MAXIMUM(getIntegerValueOrThrow<quint16>(qsettings, "regeneration_maximum")),
    CONSUMPTION_AVERAGING_RATE(getIntegerValueOrThrow<quint16>(qsettings, "consumption_averaging_rate")),
    POWER_GRAPH_AVERAGING_RATE(getIntegerValueOrThrow<quint16>(qsettings, "power_graph_averaging_rate")),
    CHARGING_TIME_REFRESH_RATE(getIntegerValueOrThrow<quint16>(qsettings, "charging_time_refresh_rate")),    
    SOC_ON_BULK_CHARGE_END(getIntegerValueOrThrow<quint8>(qsettings, "soc_on_bulk_charge_end")),
    COMMON_AVERAGING_RATE(getIntegerValueOrThrow<quint16>(qsettings, "common_averaging_rate"))
{ }

Configuration* Configuration::getInstance() {
    if (!instance) {
        QString configFilePath = QString(CONFIGURATION_FILE_LOCATION);
        QFileInfo configFile(configFilePath);
        if (!configFile.exists()) {
            throw ConfigurationException(ConfigurationException::ErrorType::MISSING_CONFIGURATION_FILE, configFilePath);
        }
        QSettings qsettings(configFilePath, QSettings::IniFormat);
        instance = new Configuration(qsettings);
    }
    return instance;
}

QString Configuration::configToString()
{
    QString configFilePath = QString(CONFIGURATION_FILE_LOCATION);
    QFileInfo configFile(configFilePath);
    if (!configFile.exists()) {
       return "No settings found";
    }
    QSettings settings(configFilePath, QSettings::IniFormat);
    QStringList keys = settings.allKeys();

    QString config;

    for(QString key: keys) {
        config.append(key + ":");
        config.append(settings.value(key).toString() + "\n");
    }
    return config;


}

QVariant Configuration::getValueOrThrow(QSettings& settings, QString key)
{
    QVariant value = settings.value(key);
    if (value.isNull()) {
        throw ConfigurationException(ConfigurationException::ErrorType::MISSING_CONFIGURATION_ITEM, key);
    }
    return value;
}

ConfigurationException::ConfigurationException(ConfigurationException::ErrorType type, QString details) : type_(type), details_(details)
{ }

template<typename T>
T Configuration::getIntegerValueOrThrow(QSettings &qsettings, QString key)
{
    QVariant value = getValueOrThrow(qsettings, key);
    bool success;
    quint64 integerValue = value.toULongLong(&success);
    if (!success) {
        throw ConfigurationException(ConfigurationException::ErrorType::INVALID_CONFIGURATION_VALUE_TYPE, key + ": " + value.toString());
    }
    T finalIntegerValue = static_cast<T>(integerValue);
    if (integerValue != finalIntegerValue) {
        throw ConfigurationException(ConfigurationException::ErrorType::CONFIGURATION_ITEM_OUT_OF_RANGE, key + ": " + value.toString());
    }
    return finalIntegerValue;
}
