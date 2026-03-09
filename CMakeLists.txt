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
list(APPEND EXECUTABLE_LIBRARIES Core)
list(APPEND TESTING_LIBRARIES Core)

if (ENABLE_GUI)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
    add_subdirectory(extern/SDL EXCLUDE_FROM_ALL)
    list(APPEND EXECUTABLE_LIBRARIES SDL3::SDL3)
endif()

# Training executable
if(BUILD_EXECUTABLE)
    add_executable(Othello 
        extern/imgui/backends/imgui_impl_sdl3.cpp
        extern/imgui/backends/imgui_impl_sdlgpu3.cpp
        extern/imgui/imgui_demo.cpp
        extern/imgui/imgui_draw.cpp
        extern/imgui/imgui_tables.cpp
        extern/imgui/imgui_widgets.cpp
        extern/imgui/imgui.cpp
        src/main.cpp
    )
   target_link_libraries(
       Othello
       ${EXECUTABLE_LIBRARIES}
   )


    target_include_directories(
        Othello 
        PUBLIC 
        "${PROJECT_BINARY_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui"
        "${CMAKE_CURRENT_SOURCE_DIR}/extern/imgui/backends"
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
        ${TESTING_LIBRARIES}
        GTest::gtest_main
    )
    include(GoogleTest)
    gtest_discover_tests(hello_test)
endif()
