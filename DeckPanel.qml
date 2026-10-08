import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: root

    color: "#111211"

    border.color: "#3a382f"
    border.width: 1

    property int deckVersion: 0

    signal commanderChanged()

    function categoryCards(category) {

        // Force QML to reevaluate this function
        // whenever the deck changes.
        var version = root.deckVersion

        return DeckManager.entries(category)
    }

    function commanderList() {

        var version = root.deckVersion

        return DeckManager.commanders()
    }

    ColumnLayout {

        anchors.fill: parent

        anchors.margins: 18

        spacing: 12

        // =========================================================
        // HEADER
        // =========================================================

        RowLayout {

            Layout.fillWidth: true

            Text {

                text: "YOUR DECK"

                color: "#c7a75a"

                font.pixelSize: 20

                font.bold: true
            }

            Item {
                Layout.fillWidth: true
            }

            Text {

                text:
                    DeckManager.cardCount +
                    " cards"

                color: "#8f8c80"

                font.pixelSize: 12
            }
        }

        Rectangle {

            Layout.fillWidth: true

            Layout.preferredHeight: 1

            color: "#3a382f"
        }

        // =========================================================
        // DECK CONTENT
        // =========================================================

        ScrollView {

            id: scrollView

            Layout.fillWidth: true
            Layout.fillHeight: true

            clip: true

            ScrollBar.vertical.policy:
                ScrollBar.AsNeeded

            Column {

                width:
                    scrollView.availableWidth

                spacing: 18

                // =================================================
                // COMMANDERS
                // =================================================

                Column {

                    width: parent.width

                    spacing: 8

                    Text {

                        text: "COMMANDER"

                        color: "#c7a75a"

                        font.pixelSize: 13

                        font.bold: true
                    }

                    Repeater {

                        model:
                            root.commanderList()

                        delegate: Rectangle {

                            width:
                                parent.width

                            height: 55

                            color: "#181a18"

                            border.color:
                                "#34352f"

                            radius: 4

                            RowLayout {

                                anchors.fill: parent

                                anchors.margins: 5

                                spacing: 8

                                Image {

                                    Layout.preferredWidth: 38

                                    Layout.fillHeight: true

                                    source:
                                        modelData.imageUrl

                                    fillMode:
                                        Image.PreserveAspectFit
                                }

                                Text {

                                    Layout.fillWidth: true

                                    text:
                                        modelData.name

                                    color: "#e2dfd5"

                                    font.pixelSize: 12

                                    elide:
                                        Text.ElideRight
                                }

                                Button {

                                    text: "×"

                                    Layout.preferredWidth: 32

                                    onClicked: {

                                        DeckManager.removeCommander(
                                            modelData.id
                                        )

                                        root.commanderChanged()
                                    }
                                }
                            }
                        }
                    }

                    Text {

                        visible:
                            root.commanderList().length === 0

                        text:
                            "No Commander added yet..."

                        color: "#66645c"

                        font.pixelSize: 12

                        font.italic: true
                    }
                }

                // =================================================
                // DECK CATEGORIES
                // =================================================

                Repeater {

                    model: rootCategoriesModel

                    delegate: Column {

                        width:
                            parent.width

                        spacing: 7

                        property string category:
                            modelData

                        Text {

                            text:
                                category.toUpperCase()

                            color: "#c7a75a"

                            font.pixelSize: 13

                            font.bold: true
                        }

                        Repeater {

                            model:
                                root.categoryCards(category)

                            delegate: Rectangle {

                                width:
                                    parent.width

                                height: 48

                                color: "#181a18"

                                border.color:
                                    "#2e302b"

                                radius: 4

                                RowLayout {

                                    anchors.fill: parent

                                    anchors.margins: 5

                                    spacing: 8

                                    Image {

                                        Layout.preferredWidth: 32

                                        Layout.fillHeight: true

                                        source:
                                            modelData.imageUrl

                                        fillMode:
                                            Image.PreserveAspectFit

                                        asynchronous: true
                                    }

                                    Text {

                                        Layout.fillWidth: true

                                        text:
                                            modelData.name

                                        color: "#ddd9ce"

                                        font.pixelSize: 11

                                        elide:
                                            Text.ElideRight
                                    }

                                    Text {

                                        text:
                                            "×" +
                                            modelData.quantity

                                        color: "#c7a75a"

                                        font.pixelSize: 11

                                        font.bold: true
                                    }

                                    Button {

                                        text: "−"

                                        Layout.preferredWidth: 28

                                        onClicked: {

                                            DeckManager.removeCard(
                                                modelData.id
                                            )
                                        }
                                    }
                                }
                            }
                        }

                        Text {

                            visible:
                                root.categoryCards(
                                    category
                                ).length === 0

                            text:
                                "No " +
                                category +
                                " added yet..."

                            color: "#66645c"

                            font.pixelSize: 11

                            font.italic: true
                        }
                    }
                }
            }
        }
    }

    // =============================================================
    // CATEGORY LIST
    // =============================================================

    property var rootCategoriesModel: [
        "Creature",
        "Instant",
        "Sorcery",
        "Enchantment",
        "Artifact",
        "Land",
        "Sideboard"
    ]
}