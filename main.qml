// main.qml
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

// Definerer hovedvinduet for applikasjonen
ApplicationWindow {
    title: "To-Do List app" // Tittelen på vinduet
    width: 400 // Bredde på vinduet
    height: 600 // Høyde på vinduet
    visible: true // Gjør vinduet synlig

    // ListView for å vise oppgavelisten
    ListView {
        id: listView
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: inputLayout.top
        model: todoModel // Setter modellen til ListView

        // Definerer hvordan hvert element (oppføring) i ListView skal se ut
        delegate: Item {
            width: listView.width // Bredden til hvert element
            height: 50 // Høyden til hvert element

            // Layout for hvert element
            RowLayout {
                anchors.fill: parent
                anchors.margins: 10

                // Definerer innholdet i hvert element
                Row {
                    // CheckBox for å markere oppgaver som fullført eller ikke
                    CheckBox {
                        id: checkBox
                        anchors.verticalCenter: parent.verticalCenter
                        checked: model.completed // Setter checkbox til å være huket av hvis oppgaven er fullført
                        onCheckedChanged: {
                            // Oppdaterer oppgavestatus til backend og viser liten infoboks
                            if (checkBox.checked) {
                                infoText.text = "✅ Fullført oppgave: " + model.name;
                                infoText.color = "darkgreen";
                                infoView.visible = true;
                            } else {
                                infoText.text = "❌ Ikke fullført oppgave: " + model.name;
                                infoText.color = "darkgreen";
                                infoView.visible = true;
                            }
                            todoModel.updateTask(index, checkBox.checked, model.name)
                        }
                    }

                    // Tekstfelt for å vise eller redigere navnet på oppgaven
                    TextField {
                        id: taskName
                        text: model.name // Setter tekst til navnet på oppgaven fra modellen
                        background: null
                        anchors.verticalCenter: parent.verticalCenter
                        readOnly: checkBox.checked // Gjør feltet skrivebeskyttet hvis oppgaven er fullført
                        onAccepted: {
                            // Lagrer ny beskrivelse når ENTER trykkes og viser liten infoboks
                            if (taskName.text !== "") {
                                infoText.text = "💾 Ny oppgave beskrivelse: " + taskName.text;
                                infoText.color = "darkgreen";
                                infoView.visible = true;
                                todoModel.updateTask(index, checkBox.checked, taskName.text)
                            } else {
                                infoText.text = "⚠️ Feilet! Ugyldig oppgave beskrivelse."
                                infoText.color = "darkred";
                                infoView.visible = true;
                                taskName.text = model.name;
                            }
                        }
                        onTextChanged: {
                            // Viser lagre-beskjed i infoboks når teksten endres
                            if (taskName.text !== model.name) {
                                infoText.text = "📝 Trykk ENTER for å lagre ny beskrivelse..";
                                infoText.color = "darkgreen";
                                infoView.visible = true;
                            }
                        }
                    }
                }

                // Sletteknapp for hver oppgave
                Button {
                    id: deleteButton
                    text: "X"
                    background: null
                    visible: model.completed // Viser knappen bare hvis oppgaven er fullført
                    Layout.alignment: Qt.AlignRight
                    onClicked: {
                        // Sletter oppgaven når knappen trykkes og viser liten infoboks
                        infoText.text = "🗑️ Slettet fullført oppgave: " + model.name;
                        infoText.color = "darkgreen";
                        infoView.visible = true;
                        todoModel.deleteTask(index);
                    }
                }
            }
        }
    }

    // Layout for å lage ny oppgaver og infoboks
    ColumnLayout {
        id: inputLayout
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        spacing: 10

        // Tekstfelt for å skrive inn ny oppgave
        TextField {
            id: taskDescription
            text: ""
            placeholderText: "Beskriv oppgaven"
            onAccepted: addTaskButton.clicked()
            Layout.fillWidth: true
        }

        // Knapp for å legge til ny oppgave
        Button {
            id: addTaskButton
            text: "Legg til ny oppgave"
            onClicked: {
                // Lager ny oppgave når knappen trykkes og viser liten infoboks
                if (taskDescription.text !== "") {
                    todoModel.addTask(taskDescription.text, false);
                    infoText.text = "🚩 Lagt til ny oppgave: " + taskDescription.text;
                    infoText.color = "darkgreen";
                    infoView.visible = true;
                    taskDescription.text = "";
                } else {
                    infoText.text = "⚠️ Feilet! Mangler oppgave beskrivelse."
                    infoText.color = "darkred";
                    infoView.visible = true;
                }
            }
            Layout.fillWidth: true
        }

        // Layout for informasjonsboks
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
