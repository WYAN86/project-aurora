import QtQuick 2.15
import QtQuick.Controls 2.15
import QtGraphicalEffects 1.0

Rectangle {
    width: parent.width
    height: parent.height
    anchors.fill: parent
    color: "#0c0c10"
    z: 1

    Behavior on opacity {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
            duration: 1250
        }
    }

    Image {
        id: aurora_logo
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 80
        width: 500
        fillMode: Image.PreserveAspectFit
        source: "../images/Aurora_Powertrains_Logo_violetti_nega.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true
        visible: true
        z: 3
    }

    Glow {
        anchors.fill: aurora_logo
        radius: 10
        samples: 13
        source: aurora_logo
        smooth: true
        z: 2

        SequentialAnimation on opacity {
            loops: Animation.Infinite
            PropertyAnimation { from: 0; to: 0.5; duration: 1500 }
            PropertyAnimation { to: 1; duration: 750 }
            PropertyAnimation { to: 1; duration: 1000 }
            PropertyAnimation { to: 0; duration: 3000 }
        }
        SequentialAnimation on color {
            loops: Animation.Infinite
            PropertyAnimation { from: "#7f2082"; to: "#35b498"; duration: 1500 }
            PropertyAnimation { to: "#7f2082"; duration: 1500 }
        }
    }

    Image {
        id: eSled_logo
        width: 520
        fillMode: Image.PreserveAspectFit
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: aurora_logo.bottom;
        anchors.topMargin: 50
        source: "../images/eSled_logo_nega_RGB.png"
        sourceSize: Qt.size(parent.width, parent.height)
        smooth: true
        visible: true
        z: 3
    }

    Glow {
        anchors.fill: eSled_logo
        radius: 10
        samples: 13
        source: eSled_logo
        smooth: true
        z: 2

        SequentialAnimation on opacity {
            loops: Animation.Infinite
            PropertyAnimation { from: 0; to: 0.5; duration: 1500 }
            PropertyAnimation { to: 1; duration: 750 }
            PropertyAnimation { to: 1; duration: 1000 }
            PropertyAnimation { to: 0; duration: 3000 }
        }
        SequentialAnimation on color {
            loops: Animation.Infinite
            PropertyAnimation { from: "#7f2082"; to: "#35b498"; duration: 1500 }
            PropertyAnimation { to: "#7f2082"; duration: 1500 }
        }
    }
}
