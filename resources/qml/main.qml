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
        initialItem: calculatorPageComponent

        pushEnter: Transition {
            ParallelAnimation {
                NumberAnimation {
                    property: "x"
                    from: stackView.width * 0.2
                    to: 0
                    duration: 350
                    easing.type: Easing.OutCubic
                }
                NumberAnimation {
                    property: "opacity"
                    from: 0.0
                    to: 1.0
                    duration: 350
                    easing.type: Easing.OutCubic
                }
                NumberAnimation {
                    property: "scale"
                    from: 0.9
                    to: 1.0
                    duration: 350
                    easing.type: Easing.OutBack
                }
            }
        }

        popExit: Transition {
            ParallelAnimation {
                NumberAnimation {
                    property: "x"
                    from: 0
                    to: stackView.width * 0.2
                    duration: 300
                    easing.type: Easing.InCubic
                }
                NumberAnimation {
                    property: "opacity"
                    from: 1.0
                    to: 0.0
                    duration: 300
                    easing.type: Easing.InCubic
                }
                NumberAnimation {
                    property: "scale"
                    from: 1.0
                    to: 0.95
                    duration: 300
                    easing.type: Easing.InOutQuad
                }
            }
        }

        Component {
            id: calculatorPageComponent
            CalculatorPage {
                onButtonClicked: stackView.push(historyPageComponent)
            }
        }

        Component {
            id: historyPageComponent
            HistoryPage {
                onButtonClicked: stackView.pop()
            }
        }
    }
}
