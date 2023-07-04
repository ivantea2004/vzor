cmake_minimum_required(VERSION 3.23)

project(vzor VERSION 0.0.0)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build examples" ON)
option(ENABLE_STATIC_RUNTIME "Enable static runtime" OFF)

if(BUILD_EXAMPLES AND BUILD_SHARED_LIBS)
    set(BUILD_EXAMPLES OFF)
    message("Build examples requires static library. To prevent build errors BUILD_EXAMPLES disabled.")
endif()

if(ENABLE_STATIC_RUNTIME)
    set(VZOR_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(VZOR_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
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

set_target_properties(vzor PROPERTIES MSVC_RUNTIME_LIBRARY ${VZOR_MSVC_RUNTIME_LIBRARY})

target_compile_features(vzor PUBLIC cxx_std_20)

find_package(stb REQUIRED)

target_link_libraries(vzor PRIVATE stb::stb)

if(BUILD_EXAMPLES)

    add_subdirectory(examples)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set_target_properties(${VZOR_EXAMPLE_TARGETS} PROPERTIES FOLDER "vzor/examples")
    set_target_properties(vzor PROPERTIES FOLDER "vzor")
    set_target_properties(${VZOR_EXAMPLE_TARGETS} PROPERTIES MSVC_RUNTIME_LIBRARY ${VZOR_MSVC_RUNTIME_LIBRARY})
    target_compile_features(${VZOR_EXAMPLE_TARGETS} PUBLIC cxx_std_20)

endif()

install(TARGETS vzor ${VZOR_EXAMPLE_TARGETS})
