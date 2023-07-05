
add_library(loader loader.hpp loader.cpp)
target_include_directories(loader PUBLIC ${VZOR_ROOT}/loader)
target_compile_features(loader PUBLIC cxx_std_20)
