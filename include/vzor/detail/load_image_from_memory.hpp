#pragma once
#include<memory>
#include<vzor/detail/pixel_traits.hpp>

namespace vzor::detail
{

	using alloc_t = void* (*)(std::size_t) noexcept;
	using dealloc_t = void(*)(void*, std::size_t) noexcept;
	
	void* load_image_from_memory_impl(
		const void* data,
		size_t size,
		size_t desired_channels,
		size_t& width, 
		size_t& height,
		size_t& channels,
		alloc_t alloc, 
		dealloc_t dealloc
	) noexcept;

	template<typename Alloc>
	auto load_image_from_memory(
		const void* data,
		size_t size,
		size_t desired_channels,
		size_t& width,
		size_t& height,
		size_t& channels,
		Alloc& alloc_
		)
	{

		thread_local Alloc* allocator = nullptr;
		allocator = &alloc_;

		using P = typename Alloc::value_type;
		using T = typename detail::pixel_traits<P>::element_type;

		static auto calc_size = [](size_t s) 
		{
			return (s + sizeof(P) - 1) / sizeof(P);
		};

		auto alloc = [](size_t size) noexcept ->void* {
			return allocator->allocate(calc_size(size));
		};

		auto dealloc = [](void* data, size_t size) noexcept {
			allocator->deallocate(reinterpret_cast<P*>(data), calc_size(size));
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
		return static_cast<T*>(image);
	}

}
