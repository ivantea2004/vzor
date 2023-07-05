
function(vzor_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE vzor loader GTest::gtest GTest::gtest_main)
    target_compile_features(${name} PRIVATE cxx_std_20)
    add_test(NAME ${name} COMMAND ${name} WORKING_DIRECTORY ${VZOR_ROOT}/images)
    set(VZOR_TEST_TARGETS ${VZOR_TEST_TARGETS} ${name} PARENT_SCOPE)
endfunction()

vzor_test(test_decode)

set(VZOR_TEST_TARGETS ${VZOR_TEST_TARGETS} PARENT_SCOPE)
