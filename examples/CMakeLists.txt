
function(vzor_example name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE vzor loader)
    target_compile_features(${name} PRIVATE cxx_std_20)
    set(VZOR_EXAMPLE_TARGETS ${VZOR_EXAMPLE_TARGETS} ${name} PARENT_SCOPE)
endfunction()

vzor_example(print_size)

set(VZOR_EXAMPLE_TARGETS print_size PARENT_SCOPE)
