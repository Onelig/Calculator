import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Button {
    id: root
    width: 87
    height: 50
    Layout.preferredWidth: 100
    Layout.preferredHeight: 100
    Layout.fillWidth: true
    Layout.fillHeight: true

    background: Rectangle {
        anchors.fill: parent
        radius: 7
        color: parent.pressed ? "#dcdcdc" : parent.hovered ? "#f0f0f0" : "#B0B0B0"
        border.color: "#B0B0B0"
        border.width: 1
        Behavior on color {
            ColorAnimation {
                duration: 150
            }
        }
    }

    contentItem: Text {
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: Math.min(parent.width, parent.height) * 0.35
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
