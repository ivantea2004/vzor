#pragma once
#include<cstddef>
#include<type_traits>
#include<tuple>
#include<array>

namespace vzor
{
namespace detail
{

	template<typename Pixel>
	struct pixel_traits
	{
		using value_type = std::remove_const_t<std::remove_reference_t<decltype(std::declval<Pixel&>()[0])>>;
		static const std::size_t size = std::tuple_size<Pixel>::value;
	};

}
}
