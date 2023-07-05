#include<vzor/detail/allocator.hpp>

#define STBI_MALLOC vzor::detail::malloc
#define STBI_FREE vzor::detail::free
#define STBI_REALLOC vzor::detail::realloc

#define STB_IMAGE_IMPLEMENTATION

#include<stb_image.h>
