import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 2.15
import MyBackend 1.0

Item {
    id: calcPage
    property string str: ""
    property string hist: ""
    property var buttonMap: ({})

    signal buttonClicked()
    
    Connections {
        target: backend

        function onStrUpdated(newStr) {
            str = newStr
        }

        function onHistUpdated(newHist) {
            hist = newHist
        }

        function onTargetButton(buttonName) {
            buttonMap[buttonName].simulateClick()
        }
    }

    GridLayout {
        id: gridLayout
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
            onClicked: backend.addPercent()
            
            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_Clear_Entry
            text: "CE"
            onClicked: backend.remove(Backend.REMOVE_STR)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_Clear
            text: "С"
            onClicked: backend.remove(Backend.REMOVE_ALL)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_remove_elem
            text: "\u232B"
            onClicked: backend.remove(Backend.REMOVE_ELEM)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_root
            text: "\u221Ax"
            onClicked: backend.addRoot()

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_lbr
            text: "("
            onClicked: backend.addBracket(true)

            Component.onCompleted: buttonMap['('] = this
        }

        MyGridButton {
            id: button_rbr
            text: ")"
            onClicked: backend.addBracket(false)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_division
            text: "\u00F7"
            onClicked: backend.addOper(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num7
            text: "7"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num8
            text: "8"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num9
            text: "9"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_mult
            text: "\u00D7"
            onClicked: backend.addOper(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num4
            text: "4"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num5
            text: "5"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num6
            text: "6"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_minus
            text: "\u2212"
            onClicked: backend.addOper('-')

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num1
            text: "1"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num2
            text: "2"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num3
            text: "3"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_plus
            text: "+"
            onClicked: backend.addOper(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_change_sign
            text: "\u00B1"
            onClicked: backend.changeSign()

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_num0
            text: "0"
            onClicked: backend.addDigit(text)

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_point
            text: "."
            onClicked: backend.addPoint()

            Component.onCompleted: buttonMap[text] = this
        }

        MyGridButton {
            id: button_equal
            text: "="
            onClicked: backend.getResult()

            Component.onCompleted: buttonMap[text] = this
        }
    }

    ColumnLayout {
        id: columnLayout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: button_show_hist.bottom
        anchors.bottom: gridLayout.top
        anchors.leftMargin: 8
        anchors.rightMargin: 8
        anchors.topMargin: 4
        anchors.bottomMargin: 5
        smooth: true
        enabled: true
        spacing: 0
        layoutDirection: Qt.RightToLeft

        Rectangle {
            id: list_history
            color: "#ffffff"
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 0.15 * columnLayout.height // 20 %

            Text {
                id: text_hist
                text: hist
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                font.pixelSize: list_history.height * 1.6
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignBottom
            }
        }

        TextInput {
            id: textInput_enter_oper
            text: str
            cursorVisible: true
            font.pixelSize: textInput_enter_oper.height / 1.3
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignBottom
            Layout.minimumHeight: 60
            font.family: "Arial"
            Layout.alignment: Qt.AlignLeft | Qt.AlignBottom
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredHeight: 0.85 * columnLayout.height // 80 %
            focus: true
            wrapMode: TextEdit.NoWrap
            readOnly: true
        }
    }

    Button {
        id: button_show_hist
        text: "\u21BA"
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.topMargin: 8
        anchors.rightMargin: 8

        property real baseSize: Math.min(Math.max(parent.height  * 0.08, 24), 50)

        width: baseSize
        height: baseSize

        background: Rectangle {
            anchors.fill: parent
            radius: 7
            color: parent.pressed ? "#dcdcdc" : parent.hovered ? "#f0f0f0" : "white"
            Behavior on color {
                ColorAnimation { duration: 150 }
            }
        }

        contentItem: Text {
            text: button_show_hist.text
            anchors.fill: parent
            color: "black"
            font.pixelSize: width * 0.5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onClicked: calcPage.buttonClicked()
    }
}
