LIBTARGET = metier
INCLUDEPATH *= $${PWD}/

LIBRARY_OUT_PWD = $$clean_path($$OUT_PWD/$$relative_path($$PWD, $$_PRO_FILE_PWD_))
LIBS += -L$${LIBRARY_OUT_PWD} -l$${LIBTARGET}

equals(CORELIBMODE, staticlib) {
    LIBEXT = .a
    PRE_TARGETDEPS += $${LIBRARY_OUT_PWD}/lib$${LIBTARGET}$${LIBEXT}
}
