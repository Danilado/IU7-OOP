cmake_minimum_required(VERSION 3.5)

project(lab_01 VERSION 0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(HEADER_LIST
"${lab_01_SOURCE_DIR}/inc/mainwindow.h"
"${lab_01_SOURCE_DIR}/inc/my_graph.h"
"${lab_01_SOURCE_DIR}/inc/my_graph_funcs.h"
"${lab_01_SOURCE_DIR}/inc/controller.h"
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ui
)

set( CMAKE_CXX_FLAGS "-Iinc")

add_library(main SHARED  src/main.cpp src/mainwindow.cpp src/my_graph.cpp src/my_graph_funcs.cpp ui/mainwindow.ui src/controller.cpp ${HEADER_LIST})
target_include_directories(main PUBLIC ./inc)
target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_compile_features(main PUBLIC cxx_std_17)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        inc/mainwindow.h
        ui/mainwindow.ui
        inc/my_graph.h
        src/my_graph.cpp
        inc/my_graph_funcs.h
        src/my_graph_funcs.cpp
        inc/controller.h
        src/controller.cpp
)

add_executable(lab_01 src/main.cpp ui/mainwindow.ui
   )
target_compile_features(lab_01 PRIVATE cxx_std_17)
target_link_libraries(lab_01 PRIVATE main Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_01)
endif()
