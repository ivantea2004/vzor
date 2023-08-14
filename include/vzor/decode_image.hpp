
/*!

    \defgroup decoding

    \brief decoding functions

    Contains functions for image decoding

*/

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

    /*!
    
   

        \ingroup decoding
    
        \brief Decodes image from memory

        Decodes image from memory, allocates buffer for decoded image using specified allocator. 
        Returns image's dimentions in out parameters.

        \param [in] data Pointer to beginning of image file in memory
        \param [in] size Size of image file in memory
        \param [in] desired_components Count of pixel components, which decoded image should have
        \param [out] width Width of decoded image
        \param [out] height Height of decoded image
        \param [out] real_components Count of pixel components of image in file
        \param [in] allocator Allocator for image allocation and internal usage

        \returns Pointer to allocated and decoded image

        \remarks Throws any exception, which allocator throws

    */
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
    /*!
    
        \example print_size.cpp

    */

}
