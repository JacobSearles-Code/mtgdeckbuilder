cmake_minimum_required(VERSION 3.16)

project(mtgDeckBuilder VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Quick
    QuickControls2
    Qml
    QmlIntegration
    Network
)

qt_standard_project_setup()

qt_add_executable(appmtgDeckBuilder
    main.cpp
    Card.h
    Card.cpp
    CardModel.h
    CardModel.cpp
    ScryfallApi.h
    ScryfallApi.cpp
    DeckManager.h
    DeckManager.cpp
)

target_link_libraries(appmtgDeckBuilder
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Qml
    Qt6::QmlIntegration
    Qt6::Network
)

qt_add_qml_module(appmtgDeckBuilder
    URI mtgDeckBuilder
    VERSION 1.0
    QML_FILES
        Main.qml
        DeckPanel.qml
)

set_target_properties(appmtgDeckBuilder PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
