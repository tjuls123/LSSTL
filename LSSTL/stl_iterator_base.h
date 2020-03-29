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
//ÌØ»¯°æ±¾
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
__STL_END_NAMESPACE
#endif