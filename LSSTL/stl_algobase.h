#pragma once
#include "stl_config.h"
#include "stl_iterator_base.h"


__STL_BEGIN_NAMESPACE

template<class T>
inline void swap(T& a, T&b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<class T>
inline const T& min(const T&a, const T&b)
{
	return b < a ? b : a;
}

template<class T>
inline const T&max(const T&a, const T&b)
{
	return a < b ? b : a;
}


template<class InputIterator, class OutputIterator, class Distance>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result,
	input_iterator_tag, Distance*)
{
	for (; first != last; ++result, ++first)
	{
		*result = *first;
	}
	return result;
}


template<class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last,
	OutputIterator reslut, random_access_iterator_tag, Distance*)
{
	for (Distance n = last - first; n > 0; --n)
	{
		*reslut = *first;
		++reslut;
		++first;
	}
	return reslut;
}

template<class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
{
	for (; first != last; ++result, ++first)
	{
		*result = *first;
	}
	return result;
}

template<class BidirectionlIterator, class Distance>
inline BidirectionlIterator __copy_backward(
	BidirectionlIterator first,
	BidirectionlIterator last,
	BidirectionlIterator result,
	bidirectional_iterator_tag, Distance*)
{
	while (first != last)
	{
		*--result = *--last;  // result 表示接受容器的end位置，不能存储数据
	}
	return result;
}


template<class BidirectionlIterator1, class BidirectionlIterator2>
inline BidirectionlIterator2 copy_backward(BidirectionlIterator1 first, BidirectionlIterator1 last, BidirectionlIterator2 result)
{
	while (first != last)
	{
		*--result = *--last;
	}
	return result;
}

//template<class InputIterator, class Size, class OutputIterator>


template<class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& val)
{
	for (; first != last; ++first)
	{
		*first = val;
	}
}

template<class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T&val)
{
	for (; n > 0; --n, ++first)
	{
		*first = val;
	}
	return first;
}
__STL_END_NAMESPACE