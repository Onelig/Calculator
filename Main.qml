import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 2.15

Window
{
    id: window
    width: 400
    height: 470

    visible: true
    minimumHeight: 470
    minimumWidth: 400
    title: qsTr("Calculator")

    GridLayout {
        id: gridLayout
        height: 293
        visible: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 0.3 * window.height
        anchors.bottomMargin: 4
        rows: 6
        columns: 4

        MyGridButton {
            id: button_percent
            text: "%"
        }

        MyGridButton {
            id: button_remove_all
            text: "CE"
        }

        MyGridButton {
            id: button_removestr
            text: "С"
        }

        MyGridButton {
            id: button_remove_elem
            text: qsTr("\u232B")
        }

        MyGridButton {
            id: button_fraction
            text: qsTr("x\u207B\u00B9")
        }

        MyGridButton {
            id: button_power
            text: qsTr("x\u00B2")
        }

        MyGridButton {
            id: button_root
            text: qsTr("\u221Ax")
        }

        MyGridButton {
            id: button_division
            text: qsTr("\u00F7")
        }

        MyGridButton {
            id: button_num7
            text: "7"
        }

        MyGridButton {
            id: button_num8
            text: "8"
        }

        MyGridButton {
            id: button_num9
            text: "9"
        }

        MyGridButton {
            id: button_mult
            text: "\u00D7"
        }

        MyGridButton {
            id: button_num4
            text: "4"
        }

        MyGridButton {
            id: button_num5
            text: "5"
        }

        MyGridButton {
            id: button_num6
            text: "6"
        }

        MyGridButton {
            id: button_minus
            text: qsTr("\u2212")
        }

        MyGridButton {
            id: button_num1
            text: "1"
        }

        MyGridButton {
            id: button_num2
            text: "2"
        }

        MyGridButton {
            id: button_num3
            text: "3"
        }

        MyGridButton {
            id: button_plus
            text: "%"
        }

        MyGridButton {
            id: button_plmin
            text: qsTr("\u00B1")
        }

        MyGridButton {
            id: button_num0
            text: "0"
        }

        MyGridButton {
            id: button_point
            text: "."
        }

        MyGridButton {
            id: button_equal
            text: "="
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 4
        anchors.bottomMargin: 0.7 * window.height
        smooth: true
        enabled: true
        spacing: 0
        layoutDirection: Qt.RightToLeft

        Button {
            id: button_show_hist
            Layout.preferredWidth: 20
            Layout.preferredHeight: 20
            text: qsTr("\u21BA")
            display: AbstractButton.TextOnly
            Layout.maximumHeight: 60
            Layout.maximumWidth: 60
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.rightMargin: 0
            Layout.topMargin: 0
            Layout.minimumHeight: 40
            Layout.minimumWidth: 40
            background: Rectangle {
                anchors.fill: parent
                radius: 7
                color: parent.pressed ? "#dcdcdc" : parent.hovered ? "#f0f0f0" : "white"
                Behavior on color {
                    ColorAnimation {
                        duration: 150
                    }
                }
            }

            contentItem: Text {
                anchors.centerIn: parent
                text: button_show_hist.text
                color: "black"
                font.pixelSize: 16
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        Rectangle {
            id: list_history
            width: 200
            height: 200
            color: "#ffffff"
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.preferredWidth: 384
            Layout.preferredHeight: 40
            Layout.minimumHeight: 20
            Layout.minimumWidth: 384
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                id: text_hist
                text: qsTr("48 * 91")
                anchors.fill: parent
                font.pixelSize: list_history.height / 1.3
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignBottom
            }
        }

        TextField {
            id: textField_enter_oper
            color: "black"
            text: "123"
            font.pixelSize: textField_enter_oper.height / 1.3
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            Layout.minimumWidth: 384
            Layout.minimumHeight: 70
            placeholderTextColor: "#88ffffff"
            Layout.fillHeight: true
            Layout.fillWidth: true
            hoverEnabled: true
            font.italic: false
            font.bold: true
            font.weight: Font.Normal
            font.family: "Arial"
            placeholderText: qsTr("")

            background: Rectangle {
                color: "white"
                radius: 5
                border.color: "white"
                border.width: 1
            }
        }
    }

}

/*##^##
Designer {
    D{i:0}D{i:1}D{i:26}D{i:33;locked:true}
}
##^##*/
