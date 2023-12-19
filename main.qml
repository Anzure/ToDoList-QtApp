import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

ApplicationWindow {
    title: "ToDo List"
    width: 400
    height: 600
    visible: true

    ListView {
        id: listView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: inputLayout.top
        model: todoModel

        delegate: Item {
            width: listView.width
            height: 50

            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                CheckBox {
                    id: checkBox
                    text: model.name
                    checked: model.completed
                    onCheckedChanged: todoModel.updateTask(index, checkBox.checked)
                }

                Button {
                    id: deleteButton
                    text: "X"
                    background: null
                    visible: model.completed
                    Layout.alignment: Qt.AlignRight
                    onClicked: {
                        infoText.text = "🗑️ Slettet fullført oppgave: " + model.name;
                        infoText.color = "darkgreen";
                        infoView.visible = true;
                        todoModel.deleteTask(index);
                    }
                }
            }
        }
    }

    ColumnLayout {
        id: inputLayout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: 10

        TextField {
            id: taskDescription
            text: ""
            placeholderText: "Beskriv oppgaven"
            onAccepted: todoModel.addTask(taskDescription.text)
            Layout.fillWidth: true
        }
        Button {
            id: addTaskButton
            text: "Legg til ny oppgave"
            onClicked: {
                if (taskDescription.text !== "") {
                    todoModel.addTask(taskDescription.text);
                    infoView.visible = false;
                    taskDescription.text = "";
                } else {
                    infoText.text = "⚠️ Feilet! Mangler oppgave beskrivelse."
                    infoText.color = "darkred";
                    infoView.visible = true;
                }
            }
            Layout.fillWidth: true
        }
        Row {
            id: infoView
            width: parent.width
            Layout.fillWidth: true
            visible: false
            spacing: 20

            Text {
                id: infoText
                text: ""
                width: parent.width - closeButton.width - 20
                Layout.fillWidth: true
                color: "#fff"
                font.pixelSize: 16
            }
            Button {
                id: closeButton
                text: "X"
                height: 30
                onClicked: infoView.visible = false
            }
        }
    }
}
