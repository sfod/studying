TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QT += qml quick widgets

SOURCES += main.cpp \
    game/game_app.cpp \
    game/game_logic.cpp \
    view/player_view.cpp \
    view/main_menu_view.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    game/game_app.hpp \
    view/iview.hpp \
    game/game_logic.hpp \
    view/player_view.hpp \
    view/main_menu_view.hpp
