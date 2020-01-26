TEMPLATE = lib
QT += sql
CONFIG += staticlib
SOURCES += \
    $$PWD/src/builder.cpp \
    $$PWD/src/model.cpp \
    $$PWD/src/collection.cpp \
    $$PWD/src/db.cpp \
    src/modelbuilder.cpp \
    src/relations/hasmanyrelation.cpp \
    src/relations/relation.cpp \
    src/relations/relationlist.cpp

HEADERS += \
    $$PWD/src/builder.h \
    $$PWD/src/model.h \
    $$PWD/src/collection.h \
    $$PWD/src/db.h \
    $$PWD/src/eloquentmodel.h \
    $$PWD/src/relations/relation.h \
    $$PWD/src/relations/eloquentrelation.h \
    src/modelbuilder.h \
    src/relations/hasmanyrelation.h \
    src/relations/relationlist.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}
