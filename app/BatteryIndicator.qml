import QtQuick 2.15
import QtQuick.Controls 2.15

// frame of the battery
Rectangle {
    id: battery
    property string highlightColor
    property string fadedColor
    property int batteryPercentage

    width: 250; height: 80
    color: "transparent"

    border.width: 5
    border.color: highlightColor
    radius: 5
    antialiasing: true

    // the contents of the battery representing charge level
    Rectangle {
        anchors.left: parent.left
        anchors.margins: parent.border.width

        width: (parent.width-2*parent.border.width)*parent.batteryPercentage/100 // (parent.width-borders)*batt%/100
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: battery.fadedColor } // faded color
            GradientStop { position: 1.0; color: battery.highlightColor } // original color
        }
        z: -1
    }

    // the knob at the end of the battery
    Rectangle {
        anchors.left: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: -parent.border.width

        radius: parent.radius
        width: 12; height: parent.height/2
        color: parent.highlightColor
    }
}
