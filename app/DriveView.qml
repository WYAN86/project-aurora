import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.0
import QtLocation 5.15
import QtPositioning 5.15

AbstractView {
    id: view
    property int batteryPercentage: 0
    property int batteryTemperature: 0
    property int batteryTrip: 0

    property int speedValue: 0

    property int rpmValue: 0

    property string driveMode: "Comfort"

    property color mainColor: "#ffffff"
    property color subColor: "#4d4d4d"
    property color ringletColor: Qt.rgba((view.subColor.r + view.mainColor.r) / 2, (view.subColor.g + view.mainColor.g) / 2, (view.subColor.b + view.mainColor.b) / 2, 1.0)

    property var powerSeries: powerHistory.series
    property var consumptionSeries: consumptionHistory.series
    property double power: 0
    property int consumption: 0

    property int graphSwitch: 0

    property var positioner: positioner

    property bool mapMode: false

    Connections {
        target: view

        function onMapModeChanged(state) {
            if (view.mapMode) {
                speedoMeter.anchors.horizontalCenter = undefined
                speedoMeter.anchors.left = middlePart.left
            }
            else {
                speedoMeter.anchors.left = undefined
                speedoMeter.anchors.horizontalCenter = middlePart.horizontalCenter
            }
        }
    }

    Rectangle {
        id: leftPart
        height: parent.height
        anchors.left: parent.left
        anchors.right: middlePart.left
        visible: !view.mapMode
        z: 1

        color: "black"

        Image {
            id: rightRinglet
            source: "/images/ringlet.png"
            width: 469
            height: 469
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            visible: false
        }

        ColorOverlay {
            anchors.fill: rightRinglet
            source: rightRinglet
            color: view.ringletColor
        }

        BatteryIndicator {
            id: battery
            width: 246; height: 84
            highlightColor: view.subColor
            fadedColor: view.mainColor
            batteryPercentage: view.batteryPercentage
            anchors.horizontalCenter: rightRinglet.horizontalCenter
            anchors.verticalCenter: rightRinglet.verticalCenter
        }

        NumberField {
            id: batteryTripLabel
            anchors.horizontalCenter: battery.horizontalCenter
            anchors.bottom: battery.top
            anchors.bottomMargin: battery.height
            value: view.batteryTrip
            labelText: "km"
            rightAlign: true
            valueSize: 45
        }

        NumberField {
            id: batteryPercentLabel
            anchors.left: battery.left
            anchors.top: battery.bottom
            anchors.leftMargin: battery.width / 5
            anchors.topMargin: 15
            value: view.batteryPercentage
            labelText: "%"
            valueSize: 45
        }

        NumberField {
            id: batteryTempLabel
            anchors.right: battery.right
            anchors.top: battery.bottom
            anchors.rightMargin: battery.width / 5
            anchors.topMargin: 15
            value: view.batteryTemperature
            labelText: "°C"
            valueSize: 45
        }
    }

    Rectangle {
        id: middlePart
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        width: view.mapMode ? parent.width : 400
        z: 0

        color: "black"

        Plugin {
            id: mapPlugin
            preferred: ["osm", "here"]
        }

        PositionSource {
            id: positioner
            active: true
        }

        Map {
            id: gpsMap
            visible: view.mapMode
            height: parent.height
            width: parent.width
            plugin: mapPlugin
            anchors.bottom: parent.bottom
            copyrightsVisible: false
            center: positioner.valid ? positioner.position.coordinate : QtPositioning.coordinate(59.91, 10.75) // Oslo
            zoomLevel: 14
            color: "#00000000"
        }

        Rectangle {
            id: roundBackground
            width: 200
            height: 200
            radius: width/2
            visible: view.mapMode
            color: "black"
            anchors.top: parent.top
            anchors.left: parent.left
        }

        Rectangle {
            width: roundBackground.width/2
            height: roundBackground.height
            visible: view.mapMode
            color: "black"
            anchors.top: parent.top
            anchors.left: parent.left
        }

        Rectangle {
            width: roundBackground.width
            height: roundBackground.height/2
            visible: view.mapMode
            color: "black"
            anchors.top: parent.top
            anchors.left: parent.left
        }

        NumberField {
            id: speedoMeter
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: view.mapMode ? 5 : 45
            anchors.leftMargin: view.mapMode ? 95 : 0
            value: view.speedValue
            labelText: "km/h"
            valueSize: 90
        }
    }

    Rectangle {
        id: rightPart
        height: parent.height
        anchors.right: parent.right
        anchors.left: middlePart.right
        visible: !view.mapMode
        z: 1

        color: "black"

        Image {
            id: leftRinglet
            source: "/images/ringlet.png"
            width: 469
            height: 469
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            mirror: true
            visible: false
        }

        // Handle mirroring correctly
        ShaderEffectSource {
            id: leftRingSource
            sourceItem: leftRinglet
            visible: false
        }

        ColorOverlay {
            anchors.fill: leftRinglet
            source: leftRingSource
            color: view.ringletColor
        }

        LineChart {
            id: powerHistory
            width: 350
            height: 225
            anchors.horizontalCenter: leftRinglet.horizontalCenter
            anchors.top: leftRinglet.top
            anchors.topMargin: 60
            mainColor: window.mainColor
            subColor: window.subColor
            opacity: view.graphSwitch === 0 ? 1 : 0
        }
        LineChart {
            id: consumptionHistory
            width: 350
            height: 225
            anchors.horizontalCenter: leftRinglet.horizontalCenter
            anchors.top: leftRinglet.top
            anchors.topMargin: 60
            mainColor: window.mainColor
            subColor: window.subColor
            graphMaxY: 250
            graphMinY: -60
            opacity: view.graphSwitch === 1 ? 1 : 0
        }

        NumberField {
            id: powerAverage
            anchors.top: powerHistory.bottom
            anchors.bottom: leftRinglet.bottom
            anchors.left: powerHistory.left
            anchors.right: powerHistory.right
            value: view.power
            labelText: "kW"
            opacity: view.graphSwitch === 0 ? 1 : 0
            decimalPoints: 1
        }
        NumberField {
            id: consumptionAverage
            anchors.top: consumptionHistory.bottom
            anchors.bottom: leftRinglet.bottom
            anchors.left: consumptionHistory.left
            anchors.right: consumptionHistory.right
            value: view.consumption
            labelText: "kWh/\n100km"
            opacity: view.graphSwitch === 1 ? 1 : 0
        }
    }
}
