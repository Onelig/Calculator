import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 2.15

Item {
    id: histPage
    signal buttonClicked()

    ListView {
        id: historyListView
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: label.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: 0
        anchors.bottomMargin: 0
        clip: true
        interactive: true

        model: backend ? backend.historyList : []

        verticalLayoutDirection: ListView.BottomToTop

        delegate: Column {
            width: historyListView.width

            Rectangle {
                width: parent.width
                height: 1
                color: "#888888"
            }

            Text {
                text: modelData
                anchors.right: parent.right
                horizontalAlignment: Text.AlignRight
                font.pixelSize: histPage.height / 11
            }
        }
    }

    Label {
        id: label
        y: 0
        height: 74
        color: "#000000"
        text: qsTr("History")
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 0
        anchors.rightMargin: 0
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.family: "Times New Roman"
        font.pointSize: 30
    }

    Button {
        id: button_return
        text: "\u25C4"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 15
        anchors.topMargin: 15

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
            text: button_return.text
            anchors.fill: parent
            color: "black"
            font.pixelSize: button_return.baseSize * 0.5
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        onClicked: histPage.buttonClicked()
    }
}
