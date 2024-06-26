cmake_minimum_required(VERSION 3.5)

project(lab_03 VERSION 0.1 LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(HEADER_LIST
"${lab_03_SOURCE_DIR}/external/nlohmann_json/single_include/nlohmann/json.hpp"
"${lab_03_SOURCE_DIR}/inc/app.hpp"
"${lab_03_SOURCE_DIR}/inc/mainwindow.hpp"
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
external/nlohmann_json/single_include/nlohmann/json.hpp

src/app.cpp

src/camera/BasePTSCAdapter.cpp
src/camera/ProjPTSCAdapter.cpp
src/camera/OrthoPTSCAdapter.cpp
src/camera/OrthogonalCamera.cpp
src/camera/ProjectionCamera.cpp
src/camera/ProjcamBuilder.cpp
src/camera/OrthocamBuilder.cpp

src/command/DrawCommand/CleanCommand.cpp
src/command/DrawCommand/RenderCommand.cpp

src/command/IoCommand/LoadCameraCommand.cpp
src/command/IoCommand/LoadModelCommand.cpp
src/command/IoCommand/SaveCameraCommand.cpp
src/command/IoCommand/SaveModelCommand.cpp

src/command/SceneEditCommand/UndoCommand.cpp
src/command/SceneEditCommand/RedoCommand.cpp
src/command/SceneEditCommand/AddObjectCommand.cpp
src/command/SceneEditCommand/RemoveObjectCommand.cpp
src/command/SceneEditCommand/RotateObjectCommand.cpp
src/command/SceneEditCommand/ScaleObjectCommand.cpp
src/command/SceneEditCommand/TranslateObjectCommand.cpp
src/command/SceneEditCommand/SetCameraCommand.cpp

src/drawer/QtDrawer.cpp
src/drawer/QtDrawerFactory.cpp

src/exception/BaseException.cpp

src/interact/KeyHandlers.cpp
src/interact/Slots.cpp
src/interact/sceneDataHelper.cpp

src/io/FileSource.cpp
src/io/StringSource.cpp
src/io/FileDestination.cpp
src/io/StringDestination.cpp
src/io/SourceSolution.cpp
src/io/DestinationSolution.cpp

src/jsonAdapter/JsonAdapterSolution.cpp
src/jsonAdapter/nlohmannJSONAdapter.cpp

src/object/Object.cpp
src/object/ObjectComposite.cpp
src/object/ObjectBuilder.cpp
src/object/ObjectDirectorSolution.cpp

src/manager/CameraManager.cpp
src/manager/DrawManager.cpp
src/manager/SceneManager.cpp
src/manager/HistoryManager.cpp
src/manager/IoManager.cpp
src/manager/TransformManager.cpp

src/math/Point2D.cpp
src/math/Point3D.cpp
src/math/TransformationMatrix.cpp
src/math/MyMath.cpp

src/model/BaseModelData.cpp
src/model/NodeEdgeListData.cpp
src/model/AdjacencyListData.cpp
src/model/WireframeModel.cpp
src/model/WireframeBuilder.cpp

src/scene/Scene.cpp

src/visitor/JSONStringifyVisitor.cpp
src/visitor/PTSCSolutionVisitor.cpp
src/visitor/RenderVisitor.cpp
src/visitor/RotateObjectVisitor.cpp
src/visitor/ScaleObjectVisitor.cpp
src/visitor/TranslateObjectVisitor.cpp
src/visitor/TransformObjectVisitor.cpp

src/jsonAdapter/BaseJSONAdapter.cpp
src/jsonAdapter/nlohmannJSONAdapter.cpp

src/mainwindow.cpp
ui/mainwindow.ui
${HEADER_LIST})

target_include_directories(main PUBLIC
inc
src/camera
src/command
src/command/DrawCommand
src/command/IoCommand
src/command/SceneEditCommand
src/common
src/drawer
src/exception
src/interact
src/io
src/jsonAdapter
src/manager
src/model
src/object
src/scene
src/visitor
src/math
external/nlohmann_json/single_include/nlohmann/
)

target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_compile_features(main PUBLIC cxx_std_20)

set(PROJECT_SOURCES
src/mainwindow.cpp
ui/mainwindow.ui
)

add_executable(lab_03 src/main.cpp ui/mainwindow.ui)
target_compile_features(lab_03 PRIVATE cxx_std_20)
target_link_libraries(lab_03 PRIVATE main Qt${QT_VERSION_MAJOR}::Widgets )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(lab_03)
endif()
