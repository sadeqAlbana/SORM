INCLUDEPATH += $$PWD/src

SOURCES += \
    $$PWD/src/builder.cpp \
    $$PWD/src/model.cpp \
    $$PWD/src/collection.cpp \
    $$PWD/src/db.cpp \
    $$PWD/src/databaseerrorexception.cpp \
    $$PWD/src/modelbuilder.cpp \
    $$PWD/src/relations/hasmanyrelation.cpp \
    $$PWD/src/relations/relation.cpp \
    $$PWD/src/relations/relationlist.cpp \
    $$PWD/src/relations/relationresult.cpp \
    $$PWD/src/relations/hasonerelation.cpp \
    $$PWD/src/relations/belongstorelation.cpp \
    $$PWD/src/relations/belongstomanyrelation.cpp \
    $$PWD/src/primarykey.cpp

HEADERS += \
    $$PWD/src/builder.h \
    $$PWD/src/model.h \
    $$PWD/src/collection.h \
    $$PWD/src/db.h \
    $$PWD/src/eloquentmodel.h \
    $$PWD/src/relations/relation.h \
    $$PWD/src/relations/eloquentrelation.h \
    $$PWD/src/databaseerrorexception.h \
    $$PWD/src/modelbuilder.h \
    $$PWD/src/relations/hasmanyrelation.h \
    $$PWD/src/relations/relationlist.h \
    $$PWD/src/relations/relationresult.h \
    $$PWD/src/relations/hasonerelation.h \
    $$PWD/src/relations/belongstorelation.h \
    $$PWD/src/relations/belongstomanyrelation.h \
    $$PWD/src/primarykey.h
