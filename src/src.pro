TEMPLATE = lib
DEFINES +=ENABLE_EXCEPTIONS
QT += sql
CONFIG += staticlib
TARGET =  SORM
SOURCES += \
    $$PWD/builder.cpp \
    $$PWD/model.cpp \
    $$PWD/collection.cpp \
    $$PWD/db.cpp \
    $$PWD/databaseerrorexception.cpp \
    $$PWD/modelbuilder.cpp \
    $$PWD/relations/hasmanyrelation.cpp \
    $$PWD/relations/relation.cpp \
    $$PWD/relations/relationlist.cpp \
    $$PWD/relations/relationresult.cpp \
    $$PWD/relations/hasonerelation.cpp \
    $$PWD/relations/belongstorelation.cpp \
    $$PWD/relations/belongstomanyrelation.cpp \
    $$PWD/primarykey.cpp

HEADERS += \
    $$PWD/builder.h \
    $$PWD/model.h \
    $$PWD/collection.h \
    $$PWD/db.h \
    $$PWD/eloquentmodel.h \
    $$PWD/relations/relation.h \
    $$PWD/relations/eloquentrelation.h \
    $$PWD/databaseerrorexception.h \
    $$PWD/modelbuilder.h \
    $$PWD/relations/hasmanyrelation.h \
    $$PWD/relations/relationlist.h \
    $$PWD/relations/relationresult.h \
    $$PWD/relations/hasonerelation.h \
    $$PWD/relations/belongstorelation.h \
    $$PWD/relations/belongstomanyrelation.h \
    $$PWD/primarykey.h



unix {
    target.path = /usr/lib
    INSTALLS += target
}
