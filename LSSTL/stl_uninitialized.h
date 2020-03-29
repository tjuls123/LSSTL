#ifndef __LS_STL_INTERNAL_UNINITIALIZED_H__
#define __LS_STL_INTERNAL_UNINITIALIZED_H__
#include "stl_config.h"
#include <vcruntime_string.h>

__STL_BEGIN_NAMESPACE

template<class InputIterator, class ForwardIterator>
inline ForwardIterator __uninitiallized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __true_type)
{
	return copy(first, last, result);
}

template<class InputIterator, class ForwardIterator>
ForwardIterator __uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, __false_type)
{
	ForwardIterator cur = result;
	for (; first != last; ++first, ++result)
	{
		_Construct(&*cur, *first);
	}
	return cur;
}


template<class InputIterator, class ForwardIterator, class T>
inline ForwardIterator __uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result, T*)
{
	using Is_POD = typename __type_traits<T>::is_POD_type;
	return __uninitialized_copy_aux(first, last, result, Is_POD());
}

/************************************************************************/
/*                           std function                                          */
/************************************************************************/
template<class InputIterator, class ForwardIterator, class T>
inline ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result)
{
	return __uninitialized_copy_aux(first, last, result, __VALUE_TYPE(result));
}

inline char* uninitialized_copy(const char* first, const char* last, char* result)
{
	memmove(result, first, last - first);
	return result + (last - first);
}


/************************************************************************/
/* uninitialized_copy_n                                                                     */
/************************************************************************/





/************************************************************************/
/* uninitialized_fill                                                                     */
/************************************************************************/
template<class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, __true_type)
{
	fill(first, last, value);
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, __false_type)
{
	ForwardIterator cur = first;
	for (; first != last; ++first, ++cur)
	{
		_Construct(&*cur, value);
	}
}


template<class ForwardIterator, class T, class U>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
{
	using Is_POD = typename __type_traits<U>::is_POD_type;
	__uninitialized_fill_aux(first, last, Is_POD());
}

template<class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value)
{
	__uninitialized_fill(first, last, __VALUE_TYPE(first));
}

__STL_END_NAMESPACE
#endif 
