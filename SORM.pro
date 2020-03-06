TEMPLATE = lib
DEFINES +=ENABLE_EXCEPTIONS
QT += sql
CONFIG += staticlib
SOURCES += \
    $$PWD/src/builder.cpp \
    $$PWD/src/model.cpp \
    $$PWD/src/collection.cpp \
    $$PWD/src/db.cpp \
    databaseerrorexception.cpp \
    src/modelbuilder.cpp \
    src/relations/hasmanyrelation.cpp \
    src/relations/hasmanythroughrelation.cpp \
    src/relations/relation.cpp \
    src/relations/relationlist.cpp \
    src/relations/relationresult.cpp \
    src/relations/hasonerelation.cpp \
    src/relations/hasonethroughrelation.cpp \
    src/relations/belongstorelation.cpp \
    src/relations/belongstomanyrelation.cpp \
    src/primarykey.cpp

HEADERS += \
    $$PWD/src/builder.h \
    $$PWD/src/model.h \
    $$PWD/src/collection.h \
    $$PWD/src/db.h \
    $$PWD/src/eloquentmodel.h \
    $$PWD/src/relations/relation.h \
    $$PWD/src/relations/eloquentrelation.h \
    databaseerrorexception.h \
    src/modelbuilder.h \
    src/relations/hasmanyrelation.h \
    src/relations/hasmanythroughrelation.h \
    src/relations/relationlist.h \
    src/relations/relationresult.h \
    src/relations/hasonerelation.h \
    src/relations/hasonethroughrelation.h \
    src/relations/belongstorelation.h \
    src/relations/belongstomanyrelation.h \
    src/primarykey.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}
