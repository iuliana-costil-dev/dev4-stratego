TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt


include(../../config.pri)

SOURCES += \
        controller/controller.cpp \
        main.cpp \
        view/view.cpp

HEADERS += \
            ../../libs/consoleColor.h \
            controller/controller.h \
            libs/consoleColor.h \
            view/view.h

DISTFILES += \
    placement_blue.txt \
    placement_red.txt



