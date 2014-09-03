TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QT += qml quick widgets

SOURCES += main.cpp \
    game/game_app.cpp \
    game/game_logic.cpp \
    view/player_view.cpp \
    view/main_menu_view.cpp \
    events/event_manager.cpp \
    events/event_data.cpp \
    events/event_caller.cpp \
    actors/actor.cpp \
    actors/actor_factory.cpp \
    actors/physics_component.cpp \
    actors/actor_keeper.cpp

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
    view/main_menu_view.hpp \
    events/event_manager.hpp \
    events/event_data.hpp \
    events/event_caller.hpp \
    actors/actor.hpp \
    actors/actor_component.hpp \
    actors/actor_factory.hpp \
    actors/physics_component.hpp \
    actors/actor_keeper.hpp

OTHER_FILES += \
    data/player.json \
    resources/pawn.png
