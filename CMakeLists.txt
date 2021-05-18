cmake_minimum_required(VERSION 3.16)
project(Curves_hierarchy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -fopenmp")

#-------------------- Create a library -----------------------------------------
#Generate the shared library from the library sources
#-------------------------------------------------------------------------------
add_library(${PROJECT_NAME}_lib SHARED
        lib/curves_hierarchy.cpp
        )

add_library(${PROJECT_NAME}_lib::lib_1 ALIAS ${PROJECT_NAME}_lib)

target_include_directories(${PROJECT_NAME}_lib
        PUBLIC
        ${PROJECT_SOURCE_DIR}/libs
        )

#------------------- Create an executable --------------------------------------
file(GLOB
        CPP_SOURCES "./*.cpp")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})

# link the new library target with the binary target
target_link_libraries( ${PROJECT_NAME}
        PRIVATE
        ${PROJECT_NAME}_lib::lib_1
        )
