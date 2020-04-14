import QtQuick 2.2
import QtQuick.Window 2.1
import QtQuick.Layouts 1.1

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
}