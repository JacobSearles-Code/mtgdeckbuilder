cmake_minimum_required(VERSION 3.16)

project(mtgDeckBuilder VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
    Quick
    QuickControls2
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

qt_add_qml_module(appmtgDeckBuilder
    URI mtgDeckBuilder
    VERSION 1.0

    QML_FILES
        Main.qml
        DeckPanel.qml
)

target_link_libraries(appmtgDeckBuilder
    PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::QuickControls2
        Qt6::Network
)

set_target_properties(appmtgDeckBuilder PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
