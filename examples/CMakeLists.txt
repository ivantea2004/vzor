
string(APPEND CMAKE_FOLDER "/examples")

add_executable(vzor_print_size print_size.cpp)

add_executable(vzor::print_size ALIAS vzor_print_size)

set_target_properties(vzor_print_size
    PROPERTIES
        OUTPUT_NAME vzor-print-size
        EXPORT_NAME print_size
)

target_link_libraries(vzor_print_size PRIVATE vzor::loader vzor::vzor)
