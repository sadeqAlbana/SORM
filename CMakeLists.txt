cmake_minimum_required(VERSION 3.16)
project(SORM VERSION 1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

if(SORM_BUILD_EXAMPLES)
add_subdirectory(examples)
endif()
