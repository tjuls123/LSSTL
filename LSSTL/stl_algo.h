#pragma once
#include "stl_config.h"
#include "stl_iterator_base.h"

__STL_BEGIN_NAMESPACE

template<class InputIterator, class UnaryPredicate>
bool all_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	while (first != last)
	{
		if (!pred(*first))
		{
			return false;
		}
		++first;
	}
	return true;
}

template<class InputIterator, class UnaryPredicate>
bool any_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	while (first != last)
	{
		if (pred(*first))
		{
			return true;
		}
		++first;
	}
	return false;
}

template<class InputIterator, class UnaryPredicate>
bool none_of(InputIterator first, InputIterator last, UnaryPredicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			return false;
		}
	}
	return true;
}

template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function func)
{
	for (; first != last; ++first)
	{
		func(*first);
	}
	return func;
}

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, T val)
{
	for (; first != last; ++first)
	{
		if (*first == val)
		{
			return first;
		}
	}
	return last;
}


template<class InputIterator, class UnaryPredicate>
InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate Pred)
{
	for (; first != last; ++first)
	{
		if (Pred(*first))
		{
			return first;
		}
	}
	return last;
}


template<class InputIterator, class UnaryPredicate>
InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate Pred)
{
	for (; first != last; ++first)
	{
		if (!Pred(*first))
		{
			return first;
		}
	}
	return last;
}


template<class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2)
{
	while (first1 != last1)
	{
		for (ForwardIterator it = first2; it != last2; ++it)
		{
			if (*it == *first1)
			{
				return first1;
			}
		}
		++first1;
	}
	return last1;
}

template<class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1, 
	ForwardIterator first2, ForwardIterator last2,
	BinaryPredicate pred)
{
	while (first1 != last1)
	{
		for (ForwardIterator it = first2; it != last2; ++it)
		{
			if (pred(*it, *first1))
			{
				return first1;
			}
		}
		++first1;
	}
	return last1;
}

template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
{
	if (first != last)
	{
		ForwardIterator next = first; ++next;
		while (next != last)
		{
			if (*first == *next)
			{
				return true;
			}
			++first; ++next;
		}
	}
	return last;
}

template<class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate pred)
{
	if (first != last)
	{
		ForwardIterator next = first; ++next;
		while (next != last)
		{
			if (pred(*first, *next))
			{
				return true;
			}
			++first; ++next;
		}
	}
	return last;
}


template<class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& val)
{
	typename iterator_traits<InputIterator>::difference_type n = 0;
	for (; first != last; ++first)
	{
		if (*first == val)
		{
			++n;
		}
	}
	return n;
}


template<class InputIterator, class BinaryPredicate>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, BinaryPredicate pred)
{
	typename iterator_traits<InputIterator>::difference_type n = 0;
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			++n;
		}
	}
	return n;
}


template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2)
{
	while (first1 != last1)
	{
		if ((*first1 == *first2))
		{
			return false;
		}
		++first1;
		++first2;
	}
	return true;
}



/************************************************************************/
/*                        Modifying sequence operations:                */
/************************************************************************/

template<class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size n, OutputIterator result)
{
	while (n--)
	{
		*result = *first;
		++result; ++first;
	}
	return result;
}

template <class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator copy_if(InputIterator first, InputIterator last,
	OutputIterator result, UnaryPredicate pred)
{
	for (; first != last; ++first)
	{
		if (pred(*first))
		{
			*result = *first;
			++result;
		}
	}
	return result;
}

// template<class InputIterator, class OutputIterator>
// OutputIterator move(InputIterator first, InputIterator last, OutputIterator result)
// {
// 	while (first != last)
// 	{
// 		*result = lsstd::move(*first);
// 		++first;
// 		++result;
// 	}
// 	return result;
// }


template<class ForwardIterator, class T, class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag)
{
	Distance len = 0;
	len = distance(first, last);
	Distance half;
	ForwardIterator middle;
	while (len > 0)
	{
		half = len >> 1;
		middle = first;
		advance(middle, half);
		if (*middle < value)
		{
			first = middle;
		}
		else
		{
			len = half;
		}
		++first;
		len = len - half - 1;
	}
	
}

template<class ForwardIterator, class T>
ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value)
{
	return __lower_bound(first, last, value, __DISTANCE_TYPE(first), forward_iterator_tag());
}

__STL_END_NAMESPACE