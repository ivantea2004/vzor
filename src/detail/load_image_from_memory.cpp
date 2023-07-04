#include<vzor/detail/load_image_from_memory.hpp>

namespace vzor::detail
{

	thread_local alloc_t allocate;
	thread_local dealloc_t deallocate;
	thread_local std::pair<void*, size_t> allocations[20];

	void* malloc(size_t size)
	{
		auto it = std::find_if(std::begin(allocations), std::end(allocations), [](auto x) {
			return x.second == 0;
		});
		if (it == std::end(allocations))
			return nullptr;
		void* ptr = allocate(size);
		if (!ptr)
			return nullptr;
		*it = {ptr, size};
		return ptr;
	}
	void free(void* ptr)
	{
		auto it = std::find_if(std::begin(allocations), std::end(allocations), [&](auto x) {
			return x.first == ptr;
		});

		if (it != std::end(allocations))
		{
			deallocate(ptr, it->second);
			*it = {nullptr, 0};
		}

	}

	void* realloc(void* ptr, size_t size)
	{
		if (!ptr)
			return malloc(size);
		else
		{
			void*new_ptr = malloc(size);
			if (!new_ptr)
				return nullptr;
			std::memcpy(new_ptr, ptr, size);
			free(ptr);
			return new_ptr;
		}
	}

}

#define STBI_MALLOC vzor::detail::malloc
#define STBI_REALLOC vzor::detail::realloc
#define STBI_FREE vzor::detail::free

#define STB_IMAGE_IMPLEMENTATION 

#include<stb_image.h>

namespace vzor::detail
{

	void* load_image_from_memory_impl(
		const void* data,
		size_t size,
		size_t desired_channels,
		size_t& width,
		size_t& height,
		size_t& channels,
		alloc_t alloc,
		dealloc_t dealloc
	) noexcept
	{
		allocate = alloc;
		deallocate = dealloc;

		int w, h, c;

		void* image = stbi_load_from_memory(static_cast<const unsigned char*>(data), size, &w, &h, &c, desired_channels);

		width = w;
		height = h;
		channels = c;

		return image;
	}

}
