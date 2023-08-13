#include<vzor/decode_image.hpp>
#include<array>
#include<utility>
#include<exception>
#include<cstring>

namespace vzor
{
namespace detail
{
    
    constexpr std::size_t max_allocations = 20;

    static thread_local std::array<std::pair<void*, std::size_t>, max_allocations> allocations;
    static thread_local std::max_align_t*(*allocate)(std::size_t) noexcept;
    static thread_local void(*deallocate)(std::max_align_t*, std::size_t) noexcept;
    
    static std::pair<void*, std::size_t>* find_place(void* ptr) noexcept
    {
        auto it = std::find_if(allocations.begin(), allocations.end(), [&](auto a){ return a.first == ptr;  });
        if(it == allocations.end())
            return nullptr;
        else
            return &*it;
    }

    void* malloc(std::size_t size) noexcept
    {
        auto free_place = find_place(nullptr);

        if(!free_place)
        {
            return nullptr;
        }
        else
        {
            std::size_t elements_count = (size + sizeof(std::max_align_t) - 1) / sizeof(std::max_align_t);
            
            std::max_align_t* data = allocate(elements_count);
            if(data)
            {
                free_place->first = data;
                free_place->second = elements_count;
            }
            return data;
        }
    }   

    void free(void* data) noexcept
    {
        if(!data)
            return;
        auto place = find_place(data);

        if(!place)
        {
            return;
        }
        else
        {
            deallocate(static_cast<std::max_align_t*>(place->first), place->second);
            place->first = nullptr;
        }
    }

    void*realloc(void* ptr, std::size_t size) noexcept
    {

        if(!ptr)
            return malloc(size);
        
        void*new_ptr = malloc(size);
        if(!new_ptr)
            return nullptr;
        
        auto place = find_place(ptr);

        std::memcpy(new_ptr, ptr, place->second * sizeof(std::max_align_t));
        
        free(ptr);
        
        return new_ptr;
    }
}
}


#define STBI_MALLOC ::vzor::detail::malloc
#define STBI_REALLOC ::vzor::detail::realloc
#define STBI_FREE ::vzor::detail::free

#define STBI_STATIC
#define STB_IMAGE_IMPLEMENTATION

#include<stb_image.h>



namespace vzor
{
namespace detail
{

    std::uint8_t* decode_image_impl(
        const void*data,
        std::size_t size,
        std::size_t desired_components,
        std::size_t& width,
        std::size_t& height,
        std::size_t& real_components,
        any_allocator alloc
        )
    {
        
        thread_local any_allocator allocator;
        thread_local std::exception_ptr allocator_exception;
        
        allocator = alloc;
        allocator_exception = nullptr;

        allocate = [](std::size_t size) noexcept->std::max_align_t* {
            try{
                return allocator.allocate(size);
            }
            catch(...)
            {
                allocator_exception = std::current_exception();
                return nullptr;
            }
        };
    
        deallocate = [](std::max_align_t* data, std::size_t size)noexcept{
            allocator.deallocate(data, size); // noexcept by standart
        };
        
        int w, h, c;
        std::uint8_t* image = stbi_load_from_memory(
                static_cast<const unsigned char*>(data),
                size,
                &w,
                &h,
                &c,
                static_cast<int>(desired_components)
            );
        
        width = w;
        height = h;
        real_components = c;
        
        if(allocator_exception)
        {

            if(image)
            {
                vzor::detail::free(image);
            }
            std::rethrow_exception(allocator_exception);
        }
        
        return image;
    }
}
}
