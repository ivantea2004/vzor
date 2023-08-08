#include<stb_image.h>
#include<vzor/detail/load_image_from_memory.hpp>

#define STBI_MALLOC vzor::detail::malloc
#define STBI_FREE vzor::detail::free
#define STBI_REALLOC vzor::detail::realloc

#define STB_IMAGE_STATIC

#define STB_IMAGE_IMPLEMENTATION

#include<stb_image.h>

namespace vzor::detail
{

	void* load_image_from_memory_impl(
		const void* data,
		std::size_t size,
		std::size_t desired_channels,
		std::size_t& width,
		std::size_t& height,
		std::size_t& channels,
		alloc_t alloc,
		dealloc_t dealloc
	) noexcept
	{
		set_allocator(alloc, dealloc);

		int w, h, c;

		void* image = stbi_load_from_memory(static_cast<const unsigned char*>(data), size, &w, &h, &c, desired_channels);

		width = w;
		height = h;
		channels = c;

		return image;
	}

}
