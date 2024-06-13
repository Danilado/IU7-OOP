cmake_minimum_required(VERSION 3.20)
project(lab_02)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(imp)
include_directories(inc)
include_directories(src)
include_directories(unit_tests)
include_directories(utils)

file(GLOB_RECURSE SOURCES inc/*.hpp inl/*.inl)

add_executable(unit_tests.exe main.cpp tests/tests.hpp common/traits.hpp ${SOURCES}
        inl/AVLTree.inl)

find_package(GTest REQUIRED)
target_include_directories(unit_tests.exe PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(unit_tests.exe PRIVATE ${GTEST_LIBRARIES} pthread)

enable_testing()

add_test(NAME unit_tests.exe COMMAND unit_tests)

find_program(VALGRIND_EXECUTABLE valgrind)
if(VALGRIND_EXECUTABLE)
    add_custom_target(valgrind
            COMMAND ${VALGRIND_EXECUTABLE} --leak-check=full -q $<TARGET_FILE:unit_tests.exe>
            DEPENDS unit_tests
            COMMENT "Running unit_tests under Valgrind"
    )
else()
    message(WARNING "Valgrind not found. Unable to create valgrind target.")
endif()
