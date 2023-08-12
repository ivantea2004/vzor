

string(APPEND CMAKE_FOLDER "/common")

add_library(vzor_load_file STATIC load_file.hpp load_file.cpp)

add_library(vzor::load_file ALIAS vzor_load_file)

set_target_properties(vzor_load_file
    PROPERTIES
        OUTPUT_NAME vzor-load-file
        EXPORT_NAME load-file
)

target_include_directories(vzor_load_file PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(vzor_load_file PUBLIC cxx_std_20)

