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

__STL_END_NAMESPACE
#endif