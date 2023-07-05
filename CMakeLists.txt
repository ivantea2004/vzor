cmake_minimum_required(VERSION 3.23)

project(vzor VERSION 0.1.0)



option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build examples" ON)
option(ENABLE_STATIC_RUNTIME "Enable static runtime" OFF)
option(BUILD_TESTING "Build testing" OFF)



if(ENABLE_STATIC_RUNTIME)
    set(VZOR_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    set(VZOR_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
endif()

if(BUILD_SHARED_LIBS)
    message(FATAL "Building shared library is not supported.")
endif()



find_package(stb REQUIRED)

set(VZOR_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
file(GLOB_RECURSE VZOR_HEADERS ${VZOR_ROOT}/include/*.hpp)
file(GLOB_RECURSE VZOR_SOURCES ${VZOR_ROOT}/src/*.cpp)

add_library(vzor ${VZOR_HEADERS} ${VZOR_SOURCES})

target_include_directories(vzor PUBLIC ${VZOR_ROOT}/include)
target_sources(vzor INTERFACE FILE_SET vzor_public_headers TYPE HEADERS BASE_DIRS include FILES ${VZOR_HEADERS})
set_target_properties(vzor PROPERTIES MSVC_RUNTIME_LIBRARY ${VZOR_MSVC_RUNTIME_LIBRARY})
target_compile_features(vzor PUBLIC cxx_std_20)
target_link_libraries(vzor PRIVATE stb::stb)




if(BUILD_EXAMPLES OR BUILD_TESTING)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON) # Use folders only if there is something else to build
    add_subdirectory(loader) # loader library is needed in examples and tests to load files
    set(VZOR_IMAGES_DIR ${VZOR_ROOT}/images) # directory with test images
endif()



if(BUILD_EXAMPLES)
    add_subdirectory(examples)
    set_target_properties(${VZOR_EXAMPLE_TARGETS} PROPERTIES MSVC_RUNTIME_LIBRARY ${VZOR_MSVC_RUNTIME_LIBRARY})
    target_compile_features(${VZOR_EXAMPLE_TARGETS} PUBLIC cxx_std_20)
    target_link_libraries(${VZOR_EXAMPLE_TARGETS} PRIVATE vzor loader)
endif()

if(BUILD_TESTING)
    set(CMAKE_CTEST_ARGUMENTS "--output-on-failure")
    find_package(GTest REQUIRED)
    enable_testing()
    add_subdirectory(test)
endif()

set_target_properties(${VZOR_EXAMPLE_TARGETS} PROPERTIES FOLDER "examples")
set_target_properties(${VZOR_TEST_TARGETS} PROPERTIES FOLDER "tests")



install(TARGETS vzor FILE_SET vzor_public_headers)
