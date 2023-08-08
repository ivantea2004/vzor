

string(APPEND CMAKE_FOLDER "/common")

add_library(vzor_loader STATIC loader.hpp loader.cpp)

add_library(vzor::loader ALIAS vzor_loader)

set_target_properties(vzor_loader
    PROPERTIES
        OUTPUT_NAME vzor-loader
        EXPORT_NAME loader
)

target_include_directories(vzor_loader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(vzor_loader PUBLIC cxx_std_20)
