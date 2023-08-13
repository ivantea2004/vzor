#include<vzor/detail/any_allocator.hpp>


namespace vzor
{
namespace detail
{

    std::max_align_t* any_allocator::allocate(std::size_t size)
    {
        return allocate_(allocator_, size);
    }

    void any_allocator::deallocate(std::max_align_t* data, std::size_t size) noexcept
    {
        return deallocate_(allocator_, data, size);
    }

}
}
