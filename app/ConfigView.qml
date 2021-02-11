import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Shapes 1.15
import QtGraphicalEffects 1.0

AbstractView {
    id: view
    property alias configText: configField.text

    Text {
        color: "white"
        id: configField
        text: driveView.positioner.valid ? "GPS active" : "GPS inactive"
    }
}
