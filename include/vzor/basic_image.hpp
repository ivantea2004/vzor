#pragma once
#include<cstddef>
#include<type_traits>
#include<memory>

namespace vzor
{

	template<typename Pixel, typename Allocator = std::allocator<Pixel>>
	class basic_image
	{
	public:

		using pixel_type = Pixel;
		using allocator_type = Allocator;

		static_assert(std::is_same_v<pixel_type, typename Allocator::value_type>, "Allocator must allocate pixels.");

		basic_image(
			pixel_type*data,
			size_t width,
			size_t height,
			allocator_type alloc
		) : 
			data_(data),
			width_(width),
			height_(height),
			alloc_(alloc)
		{}
		~basic_image()
		{
			clear();
		}

		void clear()
		{
			if (data_)
			{
				alloc_.deallocate(data_, width_ * height_);
			}
		}

		size_t width()
		{
			return width_;
		}

		size_t height()
		{
			return height_;
		}

		pixel_type* data()
		{
			return data_;
		}

	private:
		pixel_type* data_;
		size_t width_, height_;
		allocator_type alloc_;
	};

}
