#pragma once
#include<cstdint>
#include<vzor/detail/any_allocator.hpp>

namespace vzor
{
    
    namespace detail
    {
        
        VZOR_EXPORT
        std::uint8_t* decode_image_impl(
                const void*data,
                std::size_t size,
                std::size_t desired_components,
                std::size_t& width,
                std::size_t& height,
                std::size_t& real_components,
                any_allocator allocator
            );
    }

    template<typename Allocator = std::allocator<void>>
    std::uint8_t* decode_image(
            const void*data,
            std::size_t size,
            std::size_t desired_components,
            std::size_t& width,
            std::size_t& height,
            std::size_t& real_components,
            Allocator allocator = Allocator{}
        )
    {
        typename std::allocator_traits<Allocator>::template rebind_alloc<std::max_align_t> alloc(allocator);
        return detail::decode_image_impl(
                data, 
                size,
                desired_components, 
                width,
                height,
                real_components,
                alloc
            );
    }

}
