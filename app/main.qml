import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.1
import QtQuick.Shapes 1.15
import "qrc:/qmlcomponents"


Window {
    id: window
    width: 1280
    height: 720
    maximumWidth: 1280
    maximumHeight: 720
    minimumWidth: 1280
    minimumHeight: 720
    visible: true

    color: "black"

    // Remove this to remove the window screen
    //flags: Qt.FramelessWindowHint

    // Color themes for driving modes
    readonly property var drivingModes: ({
        "Eco":      ({mainColor: "#35b498", subColor: "#1d6353"}),
        "Comfort":  ({mainColor: "#ffffff", subColor: "#4d4d4d"}),
        "Peak":     ({mainColor: "#e33ae6", subColor: "#7f2082"})
    });

    function changeDriveMode(mode) {
        driveModeLabel.text = mode
        mainColor    = drivingModes[mode].mainColor
        subColor     = drivingModes[mode].subColor
    }

    // Current active color
    property color mainColor: drivingModes["Comfort"].mainColor

    Behavior on mainColor {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
            duration: 1000
        }
    }

    // Current gradient end color
    property color subColor: drivingModes["Comfort"].subColor

    Behavior on subColor {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
            duration: 1000
        }
    }

    // View configuration
    readonly property var views: ({
      INIT: 0,
      IDLE: 1,
      CHARGE: 2,
      DRIVE: 3,
      ACTIVE: 4,
      SELFTEST: 5,
      SHUTDOWN: 6,
      TRAVERSE: 7,
      FAULT: 8,
      CONFIGURE: 9,
      MAX: 10
    });

    readonly property var driveComponent: ({
        powerSeries: 0,
        consumptionSeries: 1
    });

    // Current opened view
    property int currentView: views.INIT

    // Current graph showed
    property int currentDriveComponent: driveComponent.powerSeries

    // Simulate start up
    Item {
        Timer {
            id: bootupSeq1
            interval: 500
            onTriggered: {window.openView(window.views.IDLE); bootupSeq2.start();}
            running: true
        }
        Timer {
            id: bootupSeq2
            interval: 1500
            onTriggered: {window.openView(window.views.ACTIVE); bootupSeq3.start();}
        }
        Timer {
            id: bootupSeq3
            interval: 500
            onTriggered: {window.openView(window.views.DRIVE);}
        }
    }

    // Helper function for demo purposes
    function cycleView() {
        switch(currentView) {
        case views.CHARGE:
            openView(views.CONFIGURE)
            break
        case views.DRIVE:
            openView(views.CHARGE)
            break
        case views.CONFIGURE:
            openView(views.DRIVE)
            break
        default:
            openView(views.DRIVE)
        }
    }

    // Timer for showing a Splashscreen before shutting the qt application down
    Timer {
        id: shutDownTimer
        interval: 3000
        onTriggered: Qt.quit()
    }

    // Opens a view with an id from window.views
    function openView(viewId) {
        // Do not accept state changes after shutdown sequence has started
        if (currentView === views.SHUTDOWN) {
            return
        }

        switch(viewId) {
        case views.CHARGE:
        case views.DRIVE:
        case views.CONFIGURE:
            splashView.opacity = 0
            currentView = viewId
            break
        case views.INIT:
            break
        case views.IDLE:
            break
        case views.ACTIVE:
            break
        case views.SELFTEST:
            break
        case views.SHUTDOWN:
            inputConnections.enabled = 0
            splashView.opacity = 1
            shutDownTimer.start()
            break
        case views.TRAVERSE:
            break
        case views.FAULT:
            break
        case views.CONFIGURE:
            break
        default:
        }
    }
    function cycleDriveComponents() {
        if (currentView !== views.DRIVE) {
            return
        }
        switch(currentDriveComponent){
        case driveComponent.powerSeries:
            driveView.graphSwitch = 1;
            currentDriveComponent = driveComponent.consumptionSeries
            break
        case driveComponent.consumptionSeries:
            driveView.graphSwitch = 0;
            currentDriveComponent = driveComponent.powerSeries
            break
        default:
        }

    }

    // Gear configuration
    readonly property var gears: ({
      NEUTRAL: 0,
      FORWARD: 1,
      REVERSE: 2
    });

    // Keyboard handler
    Item {
        anchors.fill: parent
        focus: true
        Keys.onPressed: {
            if (event.key === Qt.Key_Left) {
                window.changeDriveMode("Eco")
                event.accepted = true
            }
            else if (event.key === Qt.Key_Right) {
                window.changeDriveMode("Comfort")
                event.accepted = true
            }
            else if (event.key === Qt.Key_Up) {
                window.changeDriveMode("Peak")
                event.accepted = true
            }
            else if (event.key === Qt.Key_Down) {
                window.cycleView()
                event.accepted = true
            }
            else if (event.key === Qt.Key_Q) {
                window.openView(window.views.SHUTDOWN)
                event.accepted = true
            }
            else if (event.key === Qt.Key_P) {
                highBeamIndicator.visible = !highBeamIndicator.visible
                event.accepted = true
            }
            else if (event.key === Qt.Key_M) {
                driveView.mapMode = !driveView.mapMode
                event.accepted = true
            }
            else if (event.key === Qt.Key_A) {
                gearLabel.state = "Neutral"
                event.accepted = true
            }
            else if (event.key === Qt.Key_S) {
                gearLabel.state = "Reverse"
                event.accepted = true
            }
            else if (event.key === Qt.Key_D) {
                gearLabel.state = "Forward"
                event.accepted = true
            }
            else if (event.key === Qt.Key_F1){
                window.cycleDriveComponents()
                event.accepted = true
            }
        }
    }

    // Message handling for all CAN messages
    Connections {
        id: inputConnections
        target: canbuffer

        function onChargingTimeEstimate(time) {
            if (time < 0) {
                chargeView.remainingTime = "--:--";
                chargeView.departureTime = "--:--";
                return;
            }

            //Seconds till full
            var minutes = time / 60;
            const hours = Math.floor(minutes / 60);
            minutes = Math.round(minutes % 60);

            chargeView.departureTime = new Date(Date.now() + time * 1000).toLocaleTimeString([], { timeZone: 'Europe/Helsinki', hour12: false, hour: '2-digit', minute: '2-digit' });

            if(minutes < 10) {
                chargeView.remainingTime = hours.toString() + ":0" + minutes.toString();

            }
            else {
                chargeView.remainingTime = hours.toString() + ":" + minutes.toString();
            }

        }

        function onChargingTimeElapsed(time) {
            const seconds = time / 1000;
            var minutes = seconds / 60;
            const hours = Math.floor(minutes / 60);
            minutes = Math.round(minutes % 60);
            if(minutes < 10){
                chargeView.elapsedTime = hours.toString() + ":0" + minutes.toString();
            }
            else {
                chargeView.elapsedTime = hours.toString() + ":" + minutes.toString();
            }
        }

        function onSpeed(speed) {
            driveView.speedValue = Math.floor(speed)
        }

        function onPower(power) {
            driveView.power = (power / 1000).toFixed(configuration.POWER_DECIMAL_PLACES)
            chargeView.batteryPower = power.toFixed(configuration.POWER_DECIMAL_PLACES)
        }

        function onEngineTemp(temp) {
            driveView.batteryTemperature = temp
            chargeView.batteryTempr = temp
        }

        function onSoc(soc) {
            driveView.batteryPercentage = Math.floor(soc)

            socLabel.text = Math.floor(soc)
            driveView.batteryTrip = 35 * (driveView.batteryPercentage / 100)
        }

        function onOdometer(odo) {
            var odoString = Math.floor(odo / 10).toString()
            var odoPadding = ""
            for(var i=0; i < 8 - odoString.length; i++) {
                odoPadding += "0"
            }
            odometer.text = "<font color=\"#4d4d4d\">" + odoPadding + "</font><font color=\"#FFFFFF\">"+ odoString + "</font>"
        }

        function onEcoLit(status) {
            if (status) {
                window.changeDriveMode("Eco")
            }
        }

        function onStandardLit(status) {
            if (status) {
                window.changeDriveMode("Comfort")
            }
        }

        function onSportLit(status) {
            if (status) {
                window.changeDriveMode("Peak")
            }
        }
        function onConsumptionChanged(consumption){
            driveView.consumption = consumption
        }

        function onBatHigh(status) {
            hvBatteryIndicator.visible = status
        }

        function onBatLow(status) {
            batteryIndicator.visible = status
        }

        function onEngineOverheat(status) {
            motorHighTemperatureIndicator.visible = status
        }

        // Icon is wrong for now, just for testing
        function onOverheat(status) {
            motorLowTemperatureIndicator.visible = status
        }

        function onCheckEngine(status) {
            engineFaultIndicator.visible = status
        }

        function onDirection(direction) {
            switch(direction) {
            case window.gears.NEUTRAL:
                gearLabel.state = "Neutral"
                break
            case window.gears.FORWARD:
                gearLabel.state = "Forward"
                break
            case window.gears.REVERSE:
                gearLabel.state = "Reverse"
                break
            default:
                break
            }
        }
        function onVehicleMode(vehicleMode) {
            openView(vehicleMode);
        }
    }

    Item {
        id: header
        height: 45
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top

        Clock {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.rightMargin: 5
        }
    }

    DriveView {
        id: driveView
        anchors.top: header.bottom
        anchors.bottom: footer.top
        width: window.width
        mainColor: window.mainColor
        subColor: window.subColor
        opacity: window.currentView === window.views.DRIVE ? 1 : 0

        Component.onCompleted: {
            canbuffer.powerSeries = driveView.powerSeries
            canbuffer.consumptionSeries = driveView.consumptionSeries
        }
    }

    ChargeView {
        id: chargeView
        anchors.top: header.bottom
        anchors.bottom: footer.top
        width: window.width
        mainColor: window.mainColor
        subColor: window.subColor
        opacity: window.currentView === window.views.CHARGE ? 1 : 0
    }

    ConfigView {
        id: configView
        anchors.top: header.bottom
        anchors.bottom: footer.top
        width: window.width
        opacity: window.currentView === window.views.CONFIGURE ? 1 : 0
        configText: configuration.configToString()

        Column {
            anchors.right: parent.right

            Text {
                id: positionDiagnosticText
                text: driveView.positioner.valid ? "GPS active" : "GPS inactive"
                color: "white"
            }

            Text {
                text: "Longitude: " + driveView.positioner.position.coordinate.longitude
                color: "white"
            }

            Text {
                text: "Latitude: " +  driveView.positioner.position.coordinate.latitude
                color: "white"
            }
        }
    }

    // The splashcreen that is shown on startup and shut down
    Splashscreen {
        id: splashView
        anchors.top: header.bottom
        anchors.bottom: footer.top
        width: window.width
    }

    Item {
        id: footer
        height: 50
        width: window.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Text {
            id: driveModeLabel
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 5
            anchors.bottomMargin: 5
            font.pointSize: 26
            text: "Comfort"
            color: window.mainColor
        }

        Text {
            id: odometer
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            text: "<font color=\"#4d4d4d\">0000</font><font color=\"#FFFFFF\">1234</font>"
            font.pointSize: 26
        }

        Text {
            id: gearLabel
            text: "N"
            color: "white"
            anchors.right: parent.right
            anchors.rightMargin: parent.width / 3
            anchors.bottom: parent.bottom
            font.pointSize: 26

            states : [
                State {
                    name: "Forward"
                    PropertyChanges {
                        target: gearLabel
                        text: "D"
                    }
                },
                State {
                    name: "Reverse"
                    PropertyChanges {
                        target: gearLabel
                        text: "R"
                        color: "#FF4d4d"
                    }
                },
                State {
                    name: "Neutral"
                    PropertyChanges {
                        target: gearLabel
                    }
                }
            ]
        }

        Text {
            id: socLabel
            text: "100"
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin: parent.width / 3
            anchors.bottom: parent.bottom
            font.pointSize: 26
        }

        Text {
            text: "%"
            color: "#4d4d4d"
            font.pointSize: 22
            anchors.bottom: socLabel.bottom
            anchors.left: socLabel.right
            anchors.leftMargin: 5
        }

        Row {
            width: parent.width
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 5
            spacing: 10
            leftPadding: 5

            Image {
                id: highBeamIndicator
                visible: false
                source: "/images/highBeam.png"
                fillMode: Image.PreserveAspectFit
                height: parent.height
            }

            Image {
                id: motorHighTemperatureIndicator
                visible: false
                source: "/images/highTemp.png"
                fillMode: Image.PreserveAspectFit
                height: parent.height
            }

            Image {
                id: motorLowTemperatureIndicator
                visible: false
                source: "/images/lowTemp.png"
                fillMode: Image.PreserveAspectFit
                height: parent.height
            }

            Image {
                id: hvBatteryIndicator
                visible: false
                source: "/images/hvBatteryLit.png"
                fillMode: Image.PreserveAspectFit
                height: parent.height
            }

            Image {
                id: batteryIndicator
                visible: false
                source: "/images/batteryLit.png"
                fillMode: Image.PreserveAspectFit
                height: parent.height
            }

            Image {
                id: engineFaultIndicator
                visible: false
                source: "/images/engineFault.png"
                fillMode: Image.PreserveAspectFit
                height: parent.height
            }
        }
    }
}
