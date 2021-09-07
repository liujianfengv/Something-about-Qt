import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    Item {
        id: name;
        anchors.fill: parent
        Rectangle {
            visible: true
            color: "#334499";
            anchors.fill: parent
            Text {
                id: my_label
                font.pixelSize: 24
                text: qsTr("Hello，World!")
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }
}

