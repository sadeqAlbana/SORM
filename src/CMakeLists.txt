cmake_minimum_required(VERSION 3.16)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)

add_library(SORM STATIC
    eloquentmodel.h
    builder.h builder.cpp
    model.h model.cpp
    collection.h collection.cpp
    db.h db.cpp
    databaseerrorexception.h databaseerrorexception.cpp
    modelbuilder.h modelbuilder.cpp
    primarykey.h primarykey.cpp
    array.h array.cpp
    relations/relation.h relations/relation.cpp
    relations/hasmanyrelation.h relations/hasmanyrelation.cpp
    relations/relationlist.h relations/relationlist.cpp
    relations/relationresult.h relations/relationresult.cpp
    relations/hasonerelation.h relations/hasonerelation.cpp
    relations/belongstorelation.h relations/belongstorelation.cpp
    relations/belongstomanyrelation.h relations/belongstomanyrelation.cpp
)

target_link_libraries(SORM PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)

target_include_directories(SORM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
