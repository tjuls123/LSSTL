#ifndef __LS_STL_INTERNAL_ITERATOR_BASE_H__
#define __LS_STL_INTERNAL_ITERATOR_BASE_H__
#include "stl_config.h"

#include <iterator>

__STL_BEGIN_NAMESPACE

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};


template<class T, class Distance>
struct input_iterator 
{
	using iterator_category = input_iterator_tag;
	using value_type = T;
	using difference_type = Distance;
	using pointer = T * ;
	using reference = T & ;
};

template<class T, class Distance>
struct output_iterator
{
	using iterator_categoty = output_iterator_tag;
	using value_type = T;
	using difference_type = Distance;
	using pointer = T * ;
	using reference = T & ;
};

template<class T, class Distance>
struct forward_iterator
{
	using iterator_categoty = forward_iterator_tag;
	using value_type = T;
	using difference_type = Distance;
	using pointer = T * ;
	using reference = T & ;
};


template<class T, class Distance>
struct bidirectional_iterator
{
	using iterator_categoty = bidirectional_iterator_tag;
	using value_type = T;
	using difference_type = Distance;
	using pointer = T * ;
	using reference = T & ;
};


template<class T, class Distance>
struct random_access_iterator
{
	using iterator_categoty = random_access_iterator_tag;
	using value_type = T;
	using difference_type = Distance;
	using pointer = T * ;
	using reference = T & ;
};


//////////////////////////////////////////////////////////////////////////
// stl 提供一个基础的迭代器，后面的其他迭代器可以继承此迭代器，这样派生类迭代器可以符合stl的标准

template<class _Category, class _Tp, class _Distance = ptrdiff_t, class _Pointer = _Tp*, class _Reference = _Tp&>
struct iterator
{
	using iterator_category = _Category;
	using value_type = _Tp;
	using difference_type = _Distance;
	using pointer = _Pointer;
	using reference = _Reference;
};

template<class Iterator>
struct iterator_traits
{
	using iterator_category = typename Iterator::iterator_category;
	using value_type = typename Iterator::value_type;
	using difference_type = typename Iterator::difference_type;
	using pointer = typename Iterator::pointer;
	using reference = typename Iterator::reference;
};

//////////////////////////////////////////////////////////////////////////
//特化版本
template<class T>
struct iterator_traits<T*>
{
	using iterator_category = random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;
};

template<class T>
struct iterator_traits<const T*>
{
	using iterator_category = random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = const T*;
	using reference = const T&;
};


template<class Iter>
inline typename iterator_traits<Iter>::iterator_category
iterator_cagegory(const Iter& iter)
{
	using Category = typename iterator_traits<Iter>::iterator_category;
	return Category();
}

template<class Iter>
inline typename iterator_traits<Iter>::difference_type*
distance_type(const Iter& iter)
{
	return static_cast<typename iterator_traits<Iter>::difference_type*>(0);
}

template<class Iter>
inline typename iterator_traits<Iter>::value_type*
value_type(const Iter& iter)
{
	return static_cast<typename iterator_traits<Iter>::value_type*>(0);
}

template<class T, class Distance>
inline T* value_type(const input_iterator<T, Distance>&)
{
	return (T*)(0);
}

#define __ITERATOR_CATEGORY(iter) iterator_category(iter)
#define __DISTANCE_TYPE(iter)     distance_type(iter)
#define __VALUE_TYPE(iter)        value_type(iter)


template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag)
{
	typename iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last)
	{
		++n;
		++first;
	}
	return n;
}

template<class RandomAccessIterator>
typename iterator_traits<RandomAccessIterator>::difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
{
	return last - first;
}


template<class InputIterator>
typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last)
{
	return __distance(first, last, iterator_cagegory(first));
}

template<class InputIterator, class Distance>
void __advance(InputIterator first, Distance n, input_iterator_tag)
{
	while (n--)
	{
		++first;
	}
}

template<class BidirectionalIterator, class Distance>
void __advance(BidirectionalIterator first, Distance n, bidirectional_iterator_tag)
{
	if (n > 0)
	{
		while (n--)
		{
			++first;
		}
	}
	else
	{
		while (n++)
		{
			--first;
		}
	}
}

template<class RandomAccessIterator, class Distance>
void __advance(RandomAccessIterator first, Distance n, random_access_iterator_tag)
{
	first += n;
}


template<class InputIterator, class Distance>
void advance(InputIterator first, Distance n)
{
	__advance(first, n, iterator_cagegory(first));
}


__STL_END_NAMESPACE
#endif