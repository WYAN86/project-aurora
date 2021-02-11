import QtQuick 2.15

Item {
    layer.enabled: true

    Behavior on opacity {
        PropertyAnimation {
            easing.type: Easing.InOutQuad
            duration: 1250
        }
    }
}
