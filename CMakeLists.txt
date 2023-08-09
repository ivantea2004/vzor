cmake_minimum_required(VERSION 3.26)

project(vzor
    VERSION 0.1.0
    LANGUAGES CXX
)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
option(BUILD_TESTING "Build testing" OFF)

if(BUILD_TESTING AND BUILD_SHARED_LIBS)
    # On Windows test executables can not find dllls
    message(WARNING
        " BUILD_TESTING and BUILD_SHARED_LIBS are both enabled.\n"
        " Testing is not possible with shared libraries.\n"
        " Disabling BUILD_TESTING."
    )
    set(BUILD_TESTING OFF)
endif()

set(CMAKE_FOLDER "vzor")

set(CMAKE_C_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

add_library(vzor)

set_target_properties(vzor
    PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
)

add_library(vzor::vzor ALIAS vzor)

set_target_properties(vzor
    PROPERTIES
        OUTPUT_NAME vzor
        EXPORT_NAME vzor
)

include(GenerateExportHeader)

generate_export_header(
    vzor
    EXPORT_FILE_NAME vzor/export.hpp
)

target_sources(vzor
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include ${CMAKE_CURRENT_BINARY_DIR}
    FILES
        include/vzor/config.hpp
        include/vzor/basic_image.hpp
        include/vzor/decode_image.hpp
        include/vzor/image.hpp
        include/vzor/pixel_traits.hpp
        include/vzor/rgba.hpp
        include/vzor/detail/allocator.hpp
        include/vzor/detail/load_image_from_memory.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/vzor/export.hpp
    PRIVATE
        src/detail/allocator.cpp
        src/detail/load_image_from_memory.cpp
)

target_compile_features(vzor PUBLIC cxx_std_20)

find_package(stb REQUIRED)

target_link_libraries(vzor PRIVATE stb::stb)

if(BUILD_EXAMPLES OR BUILD_TESTING)
    add_subdirectory(loader)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

include(CTest)

if(BUILD_TESTING)
    find_package(GTest REQUIRED)
    add_subdirectory(test)
endif()

include(GNUInstallDirs)

install(
    TARGETS vzor
    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}
    FILE_SET HEADERS
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
