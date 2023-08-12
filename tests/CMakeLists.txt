

include(GoogleTest)

string(APPEND CMAKE_FOLDER "/tests")

add_executable(vzor_test_decode test_decode.cpp)

add_executable(vzor::test_decode ALIAS vzor_test_decode)

set_target_properties(vzor_test_decode
    PROPERTIES
        OUTPUT_NAME vzor-test-decode
        EXPORT_NAME vzor::test_decode
)

target_link_libraries(vzor_test_decode PRIVATE vzor::vzor GTest::gtest GTest::gtest_main vzor::load_file)
target_compile_features(vzor_test_decode PRIVATE cxx_std_20)

get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)


if(is_multi_config)
    set(test_dir ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
else()
    set(test_dir ${CMAKE_CURRENT_BINARY_DIR})
endif()

gtest_discover_tests(vzor_test_decode
    WORKING_DIRECTORY ${test_dir}
)

add_custom_command(
    TARGET vzor_test_decode
    COMMENT "Copying images to test directory"
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${images_directory} ${test_dir}
)
