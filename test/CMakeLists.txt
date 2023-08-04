

include(GoogleTest)

string(APPEND CMAKE_FOLDER "/tests")

add_executable(vzor_test_decode test_decode.cpp)

add_executable(vzor::test_decode ALIAS vzor_test_decode)

set_target_properties(vzor_test_decode
    PROPERTIES
        OUTPUT_NAME vzor-test-decode
        EXPORT_NAME vzor::test_decode
)

target_link_libraries(vzor_test_decode PRIVATE vzor::vzor GTest::gtest GTest::gtest_main vzor::loader)
target_compile_features(vzor_test_decode PRIVATE cxx_std_20)

gtest_discover_tests(vzor_test_decode
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../images
)

