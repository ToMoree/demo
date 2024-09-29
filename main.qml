import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Demo")

    Rectangle{
        id: idRec
        anchors.centerIn: parent
        color: "black"
        width: 200
        height: 180
        Text {
            id: name
            color: "white"
            font.pixelSize: 30
            text: qsTr("1")
            anchors.centerIn: parent
        }
    }

    Button{
        width: 120
        height: 30
        anchors.horizontalCenter: idRec.horizontalCenter
        anchors.bottom: idRec.bottom
        anchors.bottomMargin: 10
        onClicked: {
        }
    }
}
