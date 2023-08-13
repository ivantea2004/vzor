#pragma once
#include<cstddef>
#include<memory>
#include<type_traits>
#include<vzor/config.hpp>

namespace vzor
{
namespace detail
{

    class VZOR_EXPORT any_allocator
    {
    public:
        
        using value_type = std::max_align_t;
        
        any_allocator() noexcept : 
            allocator_(nullptr),
            allocate_(nullptr),
            deallocate_(nullptr)
        {}
        
        template<typename Alloc>
        any_allocator(Alloc&other) noexcept
        {
            using A = typename std::remove_cv<Alloc>::type;
            using Tr = std::allocator_traits<A>;
            static_assert(std::is_same<typename Tr::value_type, std::max_align_t>::value, "Allocator must allocate std::max_align_t.");
            allocator_ = &other;
            allocate_ = [](void* a, std::size_t size)
            {
                return static_cast<A*>(a)->allocate(size);
            };
            deallocate_ = [](void*a, std::max_align_t* data, std::size_t size) noexcept
            {
                static_cast<A*>(a)->deallocate(data, size);
            };
        }

        any_allocator(const any_allocator&) = default;
        any_allocator(any_allocator&&) = default;
        any_allocator& operator=(const any_allocator&) = default;
        any_allocator& operator=(any_allocator&&) = default;
        
        std::max_align_t* allocate(std::size_t size);
        void deallocate(std::max_align_t* data, std::size_t size) noexcept;

    private:
        void* allocator_;
        std::max_align_t* (*allocate_)(void*, std::size_t);
        void(*deallocate_)(void*, std::max_align_t*, std::size_t) noexcept;
    };

}
}
