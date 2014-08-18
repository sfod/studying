TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    view/human_view.cpp \
    game/game_app.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    view/human_view.hpp \
    game/game_app.hpp
