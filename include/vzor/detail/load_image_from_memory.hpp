#pragma once
#include<vzor/config.hpp>
#include<vzor/pixel_traits.hpp>
#include<vzor/detail/allocator.hpp>

namespace vzor::detail
{
	VZOR_EXPORT void* load_image_from_memory_impl(
		const void* data,
		std::size_t size,
		std::size_t desired_channels,
		std::size_t& width, 
		std::size_t& height,
		std::size_t& channels,
		alloc_t alloc, 
		dealloc_t dealloc
	) noexcept;

	template<typename Alloc>
	auto load_image_from_memory(
		const void* data,
		std::size_t size,
		std::size_t desired_channels,
		std::size_t& width,
		std::size_t& height,
		std::size_t& channels,
		Alloc& alloc_
		) 
	{

		thread_local Alloc* allocator = nullptr;
		allocator = &alloc_;

		using pixel_type = typename Alloc::value_type;
		
		static auto calc_size = [](std::size_t s) noexcept
		{
			return (s + sizeof(pixel_type) - 1) / sizeof(pixel_type);
		};

		static auto alloc = [](std::size_t size) noexcept ->char* {
			return reinterpret_cast<char*>(allocator->allocate(calc_size(size)));
		};

		static auto dealloc = [](char* data, std::size_t size) noexcept {
			allocator->deallocate(reinterpret_cast<pixel_type*>(data), calc_size(size));
		};

		void* image = load_image_from_memory_impl(
			data,
			size,
			desired_channels,
			width,
			height,
			channels,
			alloc,
			dealloc
		);

		return static_cast<pixel_type*>(image);
	}

}
