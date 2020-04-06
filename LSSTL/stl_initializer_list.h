#pragma once
#include "stl_config.h"
__STL_BEGIN_NAMESPACE

template<class Elem>
class initializer_list
{
public:
	using value_type = Elem;
	using size_type = size_t;

	using reference = const Elem&;
	using const_reference = const Elem&;
	using iterator = const Elem*;
	using const_iterator = const Elem*;

	constexpr initializer_list() noexcept
		: first(nullptr), last(nullptr)
	{
	}
	constexpr initializer_list(const_iterator first_arg, const_iterator last_arg) noexcept
		: first(first_arg), last(last_arg) {}

	constexpr const_iterator begin()const noexcept { return first; }
	constexpr const_iterator end() const noexcept { return last; }
	constexpr size_type size() const noexcept { return static_cast<size_type>(last - first); }

private:
	const_iterator first;
	const_iterator last;
};
__STL_END_NAMESPACE