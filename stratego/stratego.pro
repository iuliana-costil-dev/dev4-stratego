TEMPLATE = subdirs
SUBDIRS += \
    src/gui \
    src/metier \
    src/console \
    tests

src-console.depends = src/metier
src-gui.depends = src/metier
tests.depends = src/metier

QMAKE_CXXFLAGS += -werror -wpedantic
OTHER_FILES += \
    config.pri \
