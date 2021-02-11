#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QFont>
#include <QFontDatabase>
#include <QString>
#include <iostream>
#include "canbus.h"
#include "canframehandler.h"
#include "canmessages.h"
#include "configuration.h"
#include "chargingtimeestimator.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    // Calling getInstance here, so configuration is loaded and future exceptions related to configuration are avoided
    Configuration* configuration;
    try {
        configuration = Configuration::getInstance();
    }
    catch (ConfigurationException e) {
        std::cout << "Configuration exception." << std::endl;
        // what to do in this case?
    }

    Canbus* canbus;
    CanFrameHandler canHandler;
    CanSignalBuffer canBuffer;
    ChargingTimeEstimator chargeTimeEstimator;

    // Try to establish Canbus connection
    try {
        canbus = new Canbus();
        QObject::connect(canbus, &Canbus::newCanFrame, &canHandler, &CanFrameHandler::handleFrame);
        QObject::connect(&canHandler, &CanFrameHandler::newBMS_INFO1Message, &canBuffer, &CanSignalBuffer::receiveBMS_INFO1Message);
        QObject::connect(&canHandler, &CanFrameHandler::newIC_Ctrl1Message, &canBuffer, &CanSignalBuffer::receiveIC_Ctrl1Message);
        QObject::connect(&canHandler, &CanFrameHandler::newIC_Ctrl2Message, &canBuffer, &CanSignalBuffer::receiveIC_Ctrl2Message);
        QObject::connect(&canHandler, &CanFrameHandler::newIC_Ctrl3Message, &canBuffer, &CanSignalBuffer::receiveIC_Ctrl3Message);
        QObject::connect(&canHandler, &CanFrameHandler::newIC_Ctrl5Message, &canBuffer, &CanSignalBuffer::receiveIC_Ctrl5Message);
        QObject::connect(&canHandler, &CanFrameHandler::newIC_Ctrl6Message, &canBuffer, &CanSignalBuffer::receiveIC_Ctrl6Message);
        QObject::connect(&canHandler, &CanFrameHandler::newIC_Ctrl7Message, &canBuffer, &CanSignalBuffer::receiveIC_Ctrl7Message);
        engine.rootContext()->setContextProperty("canbus", canbus);
    }
    catch (const std::runtime_error &e) {
        std::cout << "Canbus exception: " << e.what() << "\nStarting Canbus in debug mode\n" << std::flush;
    }

    // Add "roboto" as default font
    auto familyID = QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    auto familyList = QFontDatabase::applicationFontFamilies(familyID);
    if (familyList.size() >= 1) {
        QFont roboto(familyList[0]);
        app.setFont(roboto);
    } else {
        std::cout << "Warning: Unable to set Roboto as default font\n" << std::flush;
    }

    engine.rootContext()->setContextProperty("canhandler", &canHandler);
    engine.rootContext()->setContextProperty("canbuffer", &canBuffer);
    engine.rootContext()->setContextProperty("configuration", configuration);
    engine.rootContext()->setContextProperty("timeEstimator", &chargeTimeEstimator);

    engine.load(url);

    return app.exec();
}
