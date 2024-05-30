cmake_minimum_required(VERSION 3.5)

project(lab_04 VERSION 0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(HEADER_LIST
"${lab_04_SOURCE_DIR}/src/common/constants.hpp"

"${lab_04_SOURCE_DIR}/src/mainwindow.cpp"
"${lab_04_SOURCE_DIR}/inc/mainwindow.hpp"

"${lab_04_SOURCE_DIR}/src/elevator/elevator.hpp"
"${lab_04_SOURCE_DIR}/src/elevator/cabin/cabin.hpp"
"${lab_04_SOURCE_DIR}/src/elevator/doors/doors.hpp"
"${lab_04_SOURCE_DIR}/src/elevator/controller/controller.hpp"
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package( Boost 1.40 REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ui
)

if(UNIX)
    set( CMAKE_CXX_FLAGS "-lboost_thread")
endif()

add_library(main SHARED
src/mainwindow.cpp
src/elevator/elevator.cpp
src/elevator/cabin/cabin.cpp
src/elevator/controller/controller.cpp
src/elevator/doors/doors.cpp
ui/mainwindow.ui
${HEADER_LIST})

target_include_directories(main PUBLIC
    ./inc
    ./src/common
    ./src/elevator
    ./src/elevator/cabin
    ./src/elevator/doors
    ./src/elevator/controller
)

set(WIN_SPECIFIC)
if(WIN32)
  set(WIN_SPECIFIC Mswsock AdvApi32 Ws2_32 wsock32)
endif()

target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES} ${WIN_SPECIFIC})
target_compile_features(main PUBLIC cxx_std_20)

set(PROJECT_SOURCES
inc/mainwindow.hpp

src/mainwindow.cpp

ui/mainwindow.ui
src/common/constants.hpp
src/common/usings.hpp

src/elevator/elevator.hpp
src/elevator/elevator.cpp

src/elevator/cabin/cabin.hpp
src/elevator/cabin/cabin.cpp

src/elevator/doors/doors.hpp
src/elevator/doors/doors.cpp

src/elevator/controller/controller.hpp
src/elevator/controller/controller.cpp
)


add_executable(lab_04 main.cpp ui/mainwindow.ui)

target_compile_features(lab_04 PRIVATE cxx_std_20)
target_link_libraries(lab_04 PRIVATE main Qt${QT_VERSION_MAJOR}::Widgets ${Boost_LIBRARIES} ${WIN_SPECIFIC})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_04)
endif()
