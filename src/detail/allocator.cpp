#include<utility>
#include<array>
#include<cstring>
#include<algorithm>
#include<vzor/detail/allocator.hpp>

namespace vzor::detail
{

	thread_local alloc_t allocate;
	thread_local dealloc_t deallocate;
	thread_local std::array<std::pair<void*, std::size_t>, 20> allocations;

	void* malloc(std::size_t size) noexcept
	{
		auto it = std::find_if(allocations.begin(), allocations.end(), [](auto x) noexcept {
			return x.second == 0;
			});
		if (it == allocations.end())
			return nullptr;
		void* ptr = allocate(size);
		if (!ptr)
			return nullptr;
		*it = { ptr, size };
		return ptr;
	}

	void free(void* ptr) noexcept
	{
		auto it = std::find_if(allocations.begin(), allocations.end(), [&](auto x) noexcept {
			return x.first == ptr;
			});

		if (it != allocations.end())
		{
			deallocate(static_cast<char*>(ptr), it->second);
			*it = { nullptr, 0 };
		}

	}

	void* realloc(void* ptr, std::size_t size) noexcept
	{
		if (!ptr)
			return malloc(size);
		else
		{
			void* new_ptr = malloc(size);
			if (!new_ptr)
				return nullptr;
			std::memcpy(new_ptr, ptr, size);
			free(ptr);
			return new_ptr;
		}
	}

	void set_allocator(alloc_t alloc, dealloc_t dealloc) noexcept
	{
		allocate = alloc;
		deallocate = dealloc;
	}

}
