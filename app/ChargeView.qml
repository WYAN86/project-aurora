import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.0

AbstractView {
    id: view

    property string departureTime: "13:15"
    property string elapsedTime: "1:03"
    property string remainingTime: "0:33"

    property int batteryPower: 76
    property int batteryTempr: 44


    property color mainColor: "#ffffff"
    property color subColor: "#4d4d4d"

    Rectangle {
        id: topPart
        width: parent.width
        anchors.top: parent.top
        height: ( parent.height * 2) / 7

        color: "black"

        Rectangle {
            id: topBox
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            Text {
                id: departureText
                text: "Departure"
                font.family: "Roboto"
                font.pointSize: 38
                color: "white"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
            }
            Text {
                id: departureNumber
                text: view.departureTime
                font.family: "Roboto"
                font.pointSize: 40
                color: "white"

                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: departureText.bottom
            }
        }
    }

    Rectangle {
        id: middlePart
        height: ( parent.height * 3) / 7
        width: parent.width
        anchors.top: topPart.bottom

        color: "black"

        Rectangle {
            id: middleBox
            width: ( parent.width / 5 )
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.top: parent.top
            color: "black"
            Image {
                id: staticLogo
                source: "/images/staticLogo.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                height: parent.height
                width: parent.width - 40
            }
        }
        Rectangle {
            id: middleLeftBox
            height: parent.height
            anchors.right: middleBox.left
            anchors.top: parent.top
            width: ( parent.width * 2 ) / 5
            color: "black"

            Text {
                id: elapsedText
                font.family: "Roboto"
                text: "Elapsed"
                font.pointSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
            }
            Text {
                id: elapsedTime
                font.family: "Roboto"
                text: view.elapsedTime
                font.pointSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.top: elapsedText.bottom
                color: "white"
            }

        }
        Rectangle {
            id: middleRightBox
            height: parent.height
            anchors.left: middleBox.right
            anchors.top: parent.top
            width: ( parent.width * 2 ) / 5
            color: "black"
            Text {
                id: remainingText
                font.family: "Roboto"
                text: "Remaining"
                font.pointSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
            }
            Text {
                id: remainingTime
                font.family: "Roboto"
                text: view.remainingTime
                font.pointSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.top: remainingText.bottom
                color: "white"
            }

        }
    }

    Rectangle {
        id: bottomPart
        height: ( parent.height * 2) / 7
        width: parent.width
        anchors.top: middlePart.bottom
        anchors.left: parent.left

        color: "black"

        Rectangle {
            id: bottomMiddleBox
            width: parent.width / 5
            height: parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            color: "black"
            Text {
                id: batteryText
                font.family: "Roboto"
                text: "Battery"
                font.pointSize: 40
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
            }
        }
        Rectangle {
            id: bottomLeftBox
            height: parent.height

            width: (parent.width * 2) / 5
            anchors.right: bottomMiddleBox.left
            color: "black"
            Text {
                id: batterPowerNumber
                font.family: "Roboto"
                text: view.batteryPower
                font.pointSize: 60
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
            }
            Text {
                id: batteryPowerSymbol
                font.family: "Roboto"
                text: "kW"
                font.pointSize: 28
                anchors.horizontalCenter: batterPowerNumber.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.top: batterPowerNumber.bottom
                color: "white"
            }

        }
        Rectangle {
            id: bottomRightBox
            height: parent.height
            anchors.left: bottomMiddleBox.right

            width: (parent.width * 2) / 5
            color: "black"
            Text {
                id: tempatureText
                font.family: "Roboto"
                text: view.batteryTempr
                font.pointSize: 60
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                color: "white"
            }
            Text {
                id: tempatureSymbol
                font.family: "Roboto"
                text: "°C"
                font.pointSize: 28
                anchors.horizontalCenter: tempatureText.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                anchors.top: tempatureText.bottom
                color: "white"
            }

        }
    }

}
