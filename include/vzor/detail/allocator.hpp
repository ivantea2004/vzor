#pragma once
#include<cstddef>

namespace vzor::detail
{

	using alloc_t = char* (*)(std::size_t);
	using dealloc_t = void(*)(char*, std::size_t);

	void* malloc(std::size_t) noexcept;
	void free(void*)noexcept;
	void* realloc(void*, std::size_t) noexcept;

	void set_allocator(alloc_t, dealloc_t) noexcept;

}
