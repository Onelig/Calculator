import QtQuick 6.2
import QtQuick.Controls 6.2
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

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: calculatorPage
    }

    CalculatorPage {
        id: calculatorPage
        onButtonClicked: stackView.push(historyPage)
    }

    HistoryPage {
        id: historyPage
        visible: false
        onButtonClicked: stackView.pop(calculatorPage)
    }
}
