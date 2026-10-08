import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

ApplicationWindow {
    id: window
    width: 1500
    height: 900
    minimumWidth: 1100
    minimumHeight: 700
    visible: true
    title: "MTG Deck Builder"
    color: "#0d0e0d"

    property string selectedCardId: ""
    property string selectedCardName: ""
    property string selectedCardImage: ""
    property string selectedCardType: ""
    property string selectedCardText: ""
    property string selectedCardMana: ""
    property bool commanderFilter: false
    property string searchText: ""
    property var categories: [
        "Creature",
        "Instant",
        "Sorcery",
        "Enchantment",
        "Artifact",
        "Land",
        "Sideboard"
    ]

    function safeModel() {
        return ScryfallApi && ScryfallApi.searchModel ? ScryfallApi.searchModel : null
    }

    function selectCard(index) {
        var model = safeModel()
        if (!model || index < 0 || index >= model.count)
            return

        var card = model.cardAt(index)
        if (!card)
            return

        cardGrid.currentIndex = index
        selectedCardId = card.id
        selectedCardName = card.name
        selectedCardImage = card.imageUrl
        selectedCardType = card.typeLine
        selectedCardText = card.oracleText
        selectedCardMana = card.manaCost
    }

    function addSelectedCard() {
        if (selectedCardId === "")
            return

        var model = safeModel()
        if (!model)
            return

        var index = cardGrid.currentIndex
        if (index < 0 || index >= model.count)
            return

        var card = model.cardAt(index)
        if (!card)
            return

        DeckManager.addCard(card)
    }

    function addSelectedCommander() {
        if (selectedCardId === "")
            return

        var model = safeModel()
        if (!model)
            return

        var index = cardGrid.currentIndex
        if (index < 0 || index >= model.count)
            return

        var card = model.cardAt(index)
        if (!card)
            return

        if (DeckManager.addCommander(card)) {
            if (commanderFilter) {
                refreshCommanderColors()
            }
        }
    }

    function refreshCommanderColors() {
        if (commanderFilter) {
            ScryfallApi.setCommanderColors(DeckManager.commanderColors)
        } else {
            ScryfallApi.setCommanderColors([])
        }
    }

    function refreshDeck() {
        deckPanel.deckVersion++
    }

    Rectangle {
        anchors.fill: parent
        color: "#0d0e0d"
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            color: "#181a18"
            border.color: "#3a382f"
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 24
                anchors.rightMargin: 24
                spacing: 18

                Text {
                    text: "PLANESWALKER'S FORGE"
                    color: "#c7a75a"
                    font.pixelSize: 23
                    font.bold: true
                    Layout.alignment: Qt.AlignVCenter
                }

                Text {
                    text: "MTG DECK BUILDER"
                    color: "#77756b"
                    font.pixelSize: 12
                    font.letterSpacing: 2
                    Layout.alignment: Qt.AlignVCenter
                }

                Item {
                    Layout.fillWidth: true
                }

                Button {
                    text: "SAVE"
                    onClicked: saveDialog.open()
                }

                Button {
                    text: "LOAD"
                    onClicked: loadDialog.open()
                }

                Button {
                    text: "EXPORT"
                    onClicked: exportDialog.open()
                }

                Button {
                    text: "CLEAR"
                    onClicked: clearConfirm.open()
                }
            }
        }

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 0

            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                color: "#0d0e0d"

                ColumnLayout {
                    anchors.fill: parent
                    anchors.leftMargin: 24
                    anchors.rightMargin: 24
                    anchors.topMargin: 20
                    anchors.bottomMargin: 20
                    spacing: 16

                    RowLayout {
                        Layout.fillWidth: true

                        TextField {
                            id: searchField
                            Layout.fillWidth: true
                            placeholderText: "Search cards..."
                            text: window.searchText

                            onTextChanged: {
                                window.searchText = text
                                searchTimer.restart()
                            }

                            color: "#e8e5da"
                            placeholderTextColor: "#77756b"
                            font.pixelSize: 15
                            background: Rectangle {
                                color: "#181a18"
                                border.color: searchField.activeFocus ? "#c7a75a" : "#3a382f"
                                radius: 4
                            }
                        }

                        Button {
                            text: "SEARCH"
                            onClicked: {
                                searchTimer.stop()
                                if (searchField.text.trim() === "") {
                                    ScryfallApi.loadRecommendations()
                                } else {
                                    ScryfallApi.searchCards(searchField.text)
                                }
                            }
                        }

                        CheckBox {
                            text: "Commander Colors"
                            palette { windowText: "white" }
                            checked: commanderFilter
                            onClicked: {
                                commanderFilter = checked
                                refreshCommanderColors()
                            }
                        }
                    }

                    Text {
                        text: ScryfallApi.loading ? "Searching Scryfall..." : (searchField.text.trim() === "" ? "Recommended cards" : "Search results")
                        color: "#c7a75a"
                        font.pixelSize: 16
                        font.bold: true
                    }

                    GridView {
                        id: cardGrid
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        clip: true
                        cellWidth: 190
                        cellHeight: 285
                        model: ScryfallApi.searchModel
                        delegate: Item {
                            width: 180
                            height: 275

                            property bool legalCard: {
                                var model = ScryfallApi.searchModel
                                if (!model || index < 0 || index >= model.count)
                                    return false

                                var card = model.cardAt(index)
                                if (!card)
                                    return false

                                return DeckManager.isLegalForCommander(card)
                            }

                            Rectangle {
                                anchors.fill: parent
                                radius: 7
                                color: legalCard ? "#181a18" : "#111211"
                                border.width: cardGrid.currentIndex === index ? 2 : 1
                                border.color: cardGrid.currentIndex === index ? "#c7a75a" : "#34352f"
                                opacity: legalCard ? 1.0 : 0.35

                                Image {
                                    anchors.fill: parent
                                    anchors.margins: 2
                                    source: imageUrl
                                    fillMode: Image.PreserveAspectFit
                                    asynchronous: true
                                    smooth: true
                                }

                                Rectangle {
                                    anchors.left: parent.left
                                    anchors.right: parent.right
                                    anchors.bottom: parent.bottom
                                    height: 52
                                    color: "#d9161616"

                                    Column {
                                        anchors.fill: parent
                                        anchors.margins: 6
                                        spacing: 2

                                        Text {
                                            text: cardName
                                            color: "white"
                                            font.pixelSize: 12
                                            font.bold: true
                                            elide: Text.ElideRight
                                            width: parent.width
                                        }

                                        Text {
                                            text: typeLine
                                            color: "#d0cdc2"
                                            font.pixelSize: 9
                                            elide: Text.ElideRight
                                            width: parent.width
                                        }
                                    }
                                }

                                MouseArea {
                                    anchors.fill: parent
                                    onClicked: {
                                        selectCard(index)
                                    }

                                    onDoubleClicked: {
                                        selectCard(index)
                                        if (legalCard) {
                                            addSelectedCard()
                                        }
                                    }
                                }
                            }
                        }

                        ScrollBar.vertical: ScrollBar {}
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 250
                        color: "#181a18"
                        border.color: "#3a382f"
                        border.width: 1
                        radius: 6
                        visible: selectedCardId !== ""

                        RowLayout {
                            anchors.fill: parent
                            anchors.margins: 14
                            spacing: 18

                            Image {
                                Layout.preferredWidth: 145
                                Layout.fillHeight: true
                                source: selectedCardImage
                                fillMode: Image.PreserveAspectFit
                                asynchronous: true
                                smooth: true
                            }

                            ColumnLayout {
                                Layout.fillWidth: true
                                Layout.fillHeight: true
                                spacing: 7

                                Text {
                                    text: selectedCardName
                                    color: "#c7a75a"
                                    font.pixelSize: 21
                                    font.bold: true
                                }

                                Text {
                                    text: selectedCardMana
                                    color: "#d0cdc2"
                                    font.pixelSize: 14
                                }

                                Text {
                                    text: selectedCardType
                                    color: "#8f8c80"
                                    font.pixelSize: 13
                                    wrapMode: Text.Wrap
                                }

                                Rectangle {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 1
                                    color: "#3a382f"
                                }

                                Text {
                                    Layout.fillWidth: true
                                    Layout.fillHeight: true
                                    text: selectedCardText
                                    color: "#d0cdc2"
                                    font.pixelSize: 13
                                    wrapMode: Text.WordWrap
                                    verticalAlignment: Text.AlignTop
                                    maximumLineCount: 7
                                    elide: Text.ElideRight
                                }

                                RowLayout {
                                    Layout.fillWidth: true

                                    Button {
                                        text: "ADD TO DECK"
                                        enabled: selectedCardId !== ""
                                        onClicked: addSelectedCard()
                                    }

                                    Button {
                                        text: "SET AS COMMANDER"
                                        enabled: selectedCardId !== ""
                                        onClicked: addSelectedCommander()
                                    }

                                    Item {
                                        Layout.fillWidth: true
                                    }
                                }
                            }
                        }
                    }
                }
            }

            DeckPanel {
                id: deckPanel
                Layout.preferredWidth: 390
                Layout.fillHeight: true

                onCommanderChanged: {
                    if (commanderFilter)
                        refreshCommanderColors()
                }
            }
        }
    }

    Timer {
        id: searchTimer
        interval: 350
        repeat: false
        onTriggered: {
            if (searchField.text.trim() === "") {
                ScryfallApi.loadRecommendations()
            } else {
                ScryfallApi.searchCards(searchField.text)
            }
        }
    }

    FileDialog {
        id: saveDialog
        title: "Save Deck"
        fileMode: FileDialog.SaveFile
        nameFilters: ["MTG Deck (*.json)"]
        onAccepted: {
            DeckManager.saveDeck(
                selectedFile.toString().replace("file://", "")
            )
        }
    }

    FileDialog {
        id: loadDialog
        title: "Load Deck"
        fileMode: FileDialog.OpenFile
        nameFilters: ["MTG Deck (*.json)"]
        onAccepted: {
            DeckManager.loadDeck(
                selectedFile.toString().replace("file://", "")
            )
            refreshCommanderColors()
            refreshDeck()
        }
    }

    FileDialog {
        id: exportDialog
        title: "Export Deck"
        fileMode: FileDialog.SaveFile
        nameFilters: ["Text Deck (*.txt)"]
        onAccepted: {
            DeckManager.exportDeck(
                selectedFile.toString().replace("file://", "")
            )
        }
    }

    MessageDialog {
        id: clearConfirm
        title: "Clear Deck"
        text: "Are you sure you want to clear the entire deck?"
        buttons: MessageDialog.Yes | MessageDialog.No

        onButtonClicked: function(button, role) {
            if (button === MessageDialog.Yes) {
                DeckManager.clearDeck()
                selectedCardId = ""
                selectedCardName = ""
                selectedCardImage = ""
                selectedCardType = ""
                selectedCardText = ""
                selectedCardMana = ""
                cardGrid.currentIndex = -1
            }
        }
    }

    Connections {
        target: DeckManager
        function onDeckChanged() {
            deckPanel.deckVersion++
        }

        function onDeckError(message) {
            console.log("Deck error:", message)
        }
    }

    Connections {
        target: ScryfallApi
        function onSearchError(message) {
            console.log("Scryfall error:", message)
        }
    }

    Component.onCompleted: {
        ScryfallApi.loadRecommendations()
    }
}
