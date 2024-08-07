CONFIG -= qt

TEMPLATE = lib

include(../../config.pri)

# CORELIBMODE (staticlib or sharedlib) is defined in the global config.pri.
CONFIG += $${CORELIBMODE}

SOURCES += \
    board.cpp \
    common_moveable_piece.cpp \
    common_piece.cpp \
    game.cpp \
    player.cpp \
    utils/subject.cpp

HEADERS += \
    Common_piece_factory.h \
    action_result.h \
    board.h \
    common_moveable_piece.h \
    common_piece.h \
    constants.h \
    direction.h \
    game.h \
    miner.h \
    model.h \
    player.h \
    playerColor.h \
    position.h \
    spy.h \
    square.h \
    state.h \
    utils/observer.h \
    utils/subject.h \
    zebra_spy.h

DISTFILES += \
    metier.pri \
    placement_blue.txt \
    placement_red.txt
