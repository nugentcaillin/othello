# CMakeList to compile othello.
# heavily based upon instructions from
# cmake.org's cmake tutorial - 
# https://cmake.org/cmake/help/book/mastering-cmake/cmake/Help/guide/tutorial/index.html

cmake_minimum_required(VERSION 3.28)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Othello VERSION 0.0)

# options
option(ENABLE_GUI "Display Training data Visually" ON)
option(BUILD_EXECUTABLE "Build executable that trains model" ON)
option(BUILD_TESTING "Build tests" OFF)

# add all the options we want in our hpp file eg. version num, gui switch
configure_file(src/othello_config.hpp.in othello_config.hpp)


# Core Library
add_library(Core 
   ${CMAKE_CURRENT_SOURCE_DIR}/src/core/hello.cpp
)
target_include_directories(
   Core 
    PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

list(APPEND LIBRARIES Core)

# Training executable
if(BUILD_EXECUTABLE)
    add_executable(Othello 
        src/main.cpp
    )
   target_link_libraries(
       Othello
       ${LIBRARIES}
   )
    target_include_directories(
        Othello 
        PUBLIC 
        "${PROJECT_BINARY_DIR}"
    )
endif()

# Tests
if(BUILD_TESTING)
    # designed using GoogleTest's primer guide - 
    # https://google.github.io/googletest/quickstart-cmake.html

    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    FetchContent_MakeAvailable(googletest)
    
    enable_testing()

    add_executable(hello_test
        tests/core/hello.cpp
    )
    target_link_libraries(
        hello_test
        ${LIBRARIES}
        GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(hello_test)
endif()
