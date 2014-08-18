TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    board_handler.cpp \
    view/human_view.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    board_handler.hpp \
    view/human_view.hpp
