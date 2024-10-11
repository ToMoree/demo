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
        visible: UpdaterViewModel.downloadVisible
        anchors.centerIn: parent
        color: "black"
        anchors.verticalCenterOffset: 0
        anchors.horizontalCenterOffset: 0
        width: 508
        height: 302
        Text {
            id: name
            color: "white"
            font.pixelSize: 20
            anchors.verticalCenterOffset: -123
            anchors.horizontalCenterOffset: -12
            text: qsTr("update test")
            anchors.centerIn: parent
        }

        Button {
            id: button
            x: 180
            y: 183
            text: qsTr("download")
            onClicked: {
                UpdaterViewModel.startDownload()
            }
        }

        ProgressBar {
            id: progressBar
            x: 180
            y: 263
            value: UpdaterViewModel.downloadProgress
        }
    }

    Button{
        y: 157
        width: 116
        height: 31
        anchors.horizontalCenter: idRec.horizontalCenter
        anchors.bottom: idRec.bottom
        anchors.horizontalCenterOffset: -15
        anchors.bottomMargin: 203
        text: "check update"
        onClicked: {
            UpdaterViewModel.checkForUpdates();
        }
    }


}
