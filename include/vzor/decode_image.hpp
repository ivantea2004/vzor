#pragma once
#include<vzor/basic_image.hpp>
#include<vzor/detail/load_image_from_memory.hpp>
#include<vzor/detail/pixel_traits.hpp>

namespace vzor
{

	template<typename Pixel, typename Allocator = std::allocator<Pixel>>
	basic_image<Pixel, Allocator> decode_image(const void* data, size_t size, Allocator alloc = Allocator{})
	{

		static_assert(std::is_same_v<Pixel, typename Allocator::value_type>, "Allocator must allocate pixels.");

		size_t width, height, channels;

		using element_type = typename detail::pixel_traits<Pixel>::element_type;
		const size_t desired_channels = detail::pixel_traits<Pixel>::channels;

		Pixel* pixel_data = reinterpret_cast<Pixel*>(detail::load_image_from_memory(data, size, desired_channels, width, height, channels, alloc));
		return basic_image<Pixel, Allocator>(pixel_data, width, height, alloc);
	}

}
