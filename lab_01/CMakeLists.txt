cmake_minimum_required(VERSION 3.5)

project(lab_01 VERSION 0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(HEADER_LIST
"${lab_01_SOURCE_DIR}/inc/controller.hpp"
"${lab_01_SOURCE_DIR}/inc/draw_model.hpp"
"${lab_01_SOURCE_DIR}/inc/draw_handlers.hpp"
"${lab_01_SOURCE_DIR}/inc/io_handlers.hpp"
"${lab_01_SOURCE_DIR}/inc/mainwindow.hpp"
"${lab_01_SOURCE_DIR}/inc/model_error.hpp"
"${lab_01_SOURCE_DIR}/inc/model_converters.hpp"
"${lab_01_SOURCE_DIR}/inc/model_file_io.hpp"
"${lab_01_SOURCE_DIR}/inc/model.hpp"
"${lab_01_SOURCE_DIR}/inc/transform_handlers.hpp"
"${lab_01_SOURCE_DIR}/inc/point.hpp"
"${lab_01_SOURCE_DIR}/inc/point_arr.hpp"
"${lab_01_SOURCE_DIR}/inc/edge.hpp"
"${lab_01_SOURCE_DIR}/inc/edge_arr.hpp"
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

add_library(main SHARED
src/controller.cpp
src/draw_model.cpp
src/draw_handlers.cpp
src/io_handlers.cpp
src/mainwindow.cpp
src/model_converters.cpp
src/model_file_io.cpp
src/model.cpp
src/transform_handlers.cpp
src/main.cpp
src/point.cpp
src/point_arr.cpp
src/edge.cpp
src/edge_arr.cpp
ui/mainwindow.ui
${HEADER_LIST})
target_include_directories(main PUBLIC ./inc)
target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_compile_features(main PUBLIC cxx_std_17)

set(PROJECT_SOURCES
src/controller.cpp
src/draw_model.cpp
src/draw_handlers.cpp
src/io_handlers.cpp
src/mainwindow.cpp
src/error.cpp
src/model_converters.cpp
src/model_file_io.cpp
src/model.cpp
src/transform_handlers.cpp
ui/mainwindow.ui
inc/controller.h
inc/draw_model.h
inc/draw_handlers.h
inc/io_handlers.h
inc/mainwindow.h
inc/model_error.h
inc/model_converters.h
inc/model_file_io.h
inc/model.h
inc/transform_handlers.h
)

add_executable(lab_01 src/main.cpp ui/mainwindow.ui
   )
target_compile_features(lab_01 PRIVATE cxx_std_17)
target_link_libraries(lab_01 PRIVATE main Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_01)
endif()
