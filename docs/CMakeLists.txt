
find_package(Doxygen REQUIRED)

set(DOXYGEN_EXTRACT_ALL ON)
set(DOXYGEN_EXAMPLE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../examples/)

doxygen_add_docs(
    vzor_docs
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/vzor/decode_image.hpp
)
