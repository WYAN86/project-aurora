#include <QtTest>
#include <QTest>
#include <QSignalSpy>
#include <QCanBusFrame>

#include "canbus.h"
#include "configuration.h"

Q_DECLARE_METATYPE(QCanBusFrame)

class Testcanbus : public QObject
{
    Q_OBJECT

public:
    Testcanbus();
    ~Testcanbus();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void test_recieve_canframe_data();
    void test_recieve_canframe();

    void test_canbus_timeout_data();
    void test_canbus_timeout();

private:
    std::unique_ptr<QCanBusDevice> canInterface_;
    Canbus* bus = nullptr;

};

Testcanbus::Testcanbus()
{

}

Testcanbus::~Testcanbus()
{

}

void Testcanbus::initTestCase()
{
    QString errorString;
    canInterface_.reset(QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"), Configuration::getInstance()->CAN_BUS_NAME, &errorString));

    try {
        if(!canInterface_){
            throw std::runtime_error(errorString.toStdString());
        }

        if(!canInterface_->connectDevice()){
            throw std::runtime_error(errorString.toStdString());
        }
    }  catch (std::runtime_error) {
       QSKIP("Can't connect to virtual can interface skipping tests");
    }

    bus = new Canbus();
    qRegisterMetaType<QCanBusFrame>();
}

void Testcanbus::cleanupTestCase()
{
    if(bus != nullptr) {
        delete bus;
    }
}

void Testcanbus::test_recieve_canframe_data()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<QCanBusFrame::FrameType>("type");
    QTest::newRow("Data frame")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 0A 00 0000 00 00")) << QCanBusFrame::DataFrame;
    QTest::newRow("Error frame")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 0A 00 0000 00 00"))<< QCanBusFrame::ErrorFrame;

}

void Testcanbus::test_recieve_canframe()
{
     QFETCH(QCanBusFrame, frame);
     QFETCH(QCanBusFrame::FrameType, type);

     frame.setFrameType(type);

     QSignalSpy spy_frame(bus, SIGNAL(newCanFrame(QCanBusFrame)));

     canInterface_->writeFrame(frame);
     QVERIFY(spy_frame.wait());

     QCanBusFrame recievedFrame = spy_frame.first().at(0).value<QCanBusFrame>();

     QCOMPARE(recievedFrame.frameType(), frame.frameType());
     QCOMPARE(recievedFrame.toString(), frame.toString());

}

void Testcanbus::test_canbus_timeout_data()
{
    QTest::addColumn<QCanBusFrame>("frame");
    QTest::addColumn<QCanBusFrame::FrameType>("type");
    QTest::newRow("Data frame")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 0A 00 0000 00 00")) << QCanBusFrame::DataFrame;
    QTest::newRow("Error frame")  << QCanBusFrame(0x102, QByteArray::fromHex("0000 0A 00 0000 00 00"))<< QCanBusFrame::ErrorFrame;
}

void Testcanbus::test_canbus_timeout()
{
    QFETCH(QCanBusFrame, frame);
    QFETCH(QCanBusFrame::FrameType, type);

    frame.setFrameType(type);

    QSignalSpy spy_timeout(bus, SIGNAL(timeout()));
    QSignalSpy spy_timeout_cancel(bus, SIGNAL(timeoutCanceled()));

    QVERIFY(spy_timeout.wait(20000));

    canInterface_->writeFrame(frame);

    QVERIFY(spy_timeout_cancel.wait());
}

QTEST_GUILESS_MAIN(Testcanbus)

#include "tst_canbus.moc"
