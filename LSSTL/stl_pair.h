#pragma once
#include "stl_config.h"

__STL_BEGIN_NAMESPACE

template<class T1, class T2>
struct pair
{
	using first_type = T1;
	using second_type = T2;

	first_type first;
	second_type second;

	pair() : first(first_type()), second(second_type()) {}
	pair(const first_type& val1, const second_type& val2) : first(val1), second(val2) {}
};

template<class T1, class T2>
bool operator==(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
{
	return p1.first == p2.first && p1.second == p2.second;
}

template <class _T1, class _T2>
inline bool operator!=(const pair<_T1, _T2>& __x, const pair<_T1, _T2>& __y) {
	return !(__x == __y);
}

template<class T1, class T2>
bool operator<(const pair<T1, T2>& p1, const pair<T1, T2>& p2)
{
	return (p1.first < p2.first) or (!(p2.first < p1.first) && p1.second < p2.second);
}


template<class T1, class T2>
pair<T1, T2> make_pair(const T1& first, const T2& second)
{
	return pair<T1, T2>(first, second);
}
__STL_END_NAMESPACE