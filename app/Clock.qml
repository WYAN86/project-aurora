import QtQuick 2.0

Text {
    id: clock
    text: Qt.formatTime(new Date(), "hh:mm")
    Timer { interval: 5000; onTriggered: clock.text = Qt.formatTime(new Date(), "hh:mm"); running: true; repeat: true }
    color: "white"
    font.pointSize: 26
}
