cmake_minimum_required(VERSION 3.5)

project(lab_03 VERSION 0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(HEADER_LIST
"${lab_03_SOURCE_DIR}/external/nlohmann_json/single_include/nlohmann/json.hpp"

"${lab_03_SOURCE_DIR}/src/command/BaseCommand.hpp"

"${lab_03_SOURCE_DIR}/inc/mainwindow.hpp"
"${lab_03_SOURCE_DIR}/inc/app.hpp"
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ui
)

set( CMAKE_CXX_FLAGS "-Iinc")

add_library(main SHARED
src/mainwindow.cpp
ui/mainwindow.ui
${HEADER_LIST})
target_include_directories(main PUBLIC ./inc)
target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_compile_features(main PUBLIC cxx_std_20)

set(PROJECT_SOURCES
external/nlohmann_json/single_include/nlohmann/json.hpp

src/command/BaseCommand.hpp

inc/mainwindow.hpp
inc/app.hpp

src/app.cpp
src/mainwindow.cpp

ui/mainwindow.ui
)

add_executable(lab_03 src/main.cpp ui/mainwindow.ui)
target_compile_features(lab_03 PRIVATE cxx_std_20)
target_link_libraries(lab_03 PRIVATE main Qt${QT_VERSION_MAJOR}::Widgets )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_03)
endif()
