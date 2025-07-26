import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick.Layouts 2.15

Item {
    id: histPage
    signal buttonClicked()

    Button {
        id: backButton
        x: 227
        y: 227
        text: qsTr("Button")
        onClicked: histPage.buttonClicked()
    }
}
