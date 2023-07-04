cmake_minimum_required(VERSION 3.23)

project(vzor VERSION 0.0.0)

option(BUILD_SHARED_LIBS "build shared libraries" OFF)
option(BUILD_EXAMPLES "build examples" ON)

if(BUILD_EXAMPLES AND BUILD_SHARED_LIBS)
    set(BUILD_EXAMPLES OFF)
    message("Build examples requires static library. To prevent build errors BUILD_EXAMPLES disabled.")
endif()

if(BUILD_SHARED_LIBS)

    message(FATAL "Build shared library is not supported.")

endif()

set(VZOR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE VZOR_HEADERS ${VZOR_ROOT}/include/*.hpp)
file(GLOB_RECURSE VZOR_SOURCES ${VZOR_ROOT}/src/*.cpp)

add_library(vzor ${VZOR_HEADERS} ${VZOR_SOURCES})

add_library(vzor::vzor ALIAS vzor)

target_include_directories(vzor PUBLIC ${VZOR_ROOT}/include)

set_target_properties(vzor PROPERTIES PUBLIC_HEADER "${VZOR_HEADERS}")



if(BUILD_EXAMPLES)

    add_subdirectory(examples)

    set_target_properties(${VZOR_EXAMPLE_TARGETS} PROPERTIES FOLDER examples)
    set_target_properties(vzor PROPERTIES FOLDER vzor)

endif()

install(TARGETS vzor ${VZOR_EXAMPLE_TARGETS})

