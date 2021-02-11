import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    property string fontName: ""

    // Value displayed
    property double value: 99
    // Decimal Points
    property int decimalPoints: 0
    // Label under the value
    property string labelText: "-"

    // Color of the value text
    property color valueColor: "#ffffff"
    // Color of the label under the value
    property color labelColor: "#4d4d4d"

    // Size of the value text
    property int valueSize: 46
    // Size of the label text
    property int labelSize: 26

    // Align label on right side of the value instead of below
    property bool rightAlign: false

    // Encapsulate children in a box. This way the root object's size can be changed,
    // without affecting the children directly and cause wobbly positioning due to value changes.
    Item {
        width: childrenRect.width
        height: childrenRect.height
        anchors.horizontalCenter: parent.horizontalCenter

        Text {
            id: valueText
            text: value.toFixed(decimalPoints)
            font.family: fontName
            font.pointSize: valueSize
            color: valueColor
        }

        Text {
            text: labelText
            font.family: fontName
            font.pointSize: labelSize
            color: labelColor
            anchors.horizontalCenter: rightAlign ? undefined : valueText.horizontalCenter
            anchors.top: rightAlign ? undefined : valueText.bottom
            anchors.bottom: rightAlign ? valueText.bottom : undefined
            anchors.left: rightAlign ? valueText.right : undefined
            anchors.leftMargin: rightAlign ? 10 : 0
        }
    }
}
