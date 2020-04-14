import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1
import QQmlEngine
import QStringListModel
import QObject

Window {
    visible: true
    width: 640
    height: 480

    Rectangle {
        color: "#baab9e"
        anchors.fill: parent
        focus: true

        Keys.onPressed: {
            if (event.key==Qt.Key_Up) {damierqml.MouvementDamier(0)}
            if (event.key==Qt.Key_Right) {damierqml.MouvementDamier(2)}
            if (event.key==Qt.Key_Left) {damierqml.MouvementDamier(3)}
            if (event.key==Qt.Key_Down) {damierqml.MouvementDamier(1)}
        }

        ColumnLayout {
            anchors.fill: parent
            RowLayout {
                Text {
                    text: {
                        if (damierqml.Win) {
                            return "Tu as gagné bravo"
                        } else if (damierqml.Lost) {
                            return "Perdu dommage";
                        } else {
                            return "";
                        }
                    }
                    color: "white"
                    opacity: 0.3
                    font.pointSize: 30
                    font.family: "Georgia"
                    Layout.fillWidth: true
                }
                Text {
                    text: damierqml.Get_Score
                    color: "#f3eaea"
                    opacity: 0.3
                    font.pointSize: 30
                    font.family: "Georgia"
                }
            }
            Grid {
                y: 10
                anchors.horizontalCenter: parent.horizontalCenter
                rows: 4
                columns: 4
                spacing: 10

                Repeater {
                    model: damierqml
                    delegate: LesCases {
                        value: display
                        state : display
                    }
                }
            }
        }
    }
}