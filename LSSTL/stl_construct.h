#ifndef __LS_STL_INTERNAL_CONSTRUCT_H__
#define __LS_STL_INTERNAL_CONSTRUCT_H__
#include "stl_config.h"
#include "type_traits.h"

__STL_BEGIN_NAMESPACE

template<class T1, class T2>
inline void _Construct(T1* p, const T2& value)
{
	new((void*)p) T1(value);
}

template<class T1>
inline void _Construct(T1* p)
{
	new ((void*)p) T1();
}


template<class Tp>
inline void _Destroy(Tp* pointer)
{
	pointer->~Tp();
}

template<class ForwardIterator>
void __destroy_aux(ForwardIterator first, ForwardIterator last, false_type)
{
	for (; first != last; ++first)
	{
		destroy(&*first);
	}
}

template<class ForwardIterator>
void __destroy_aux(ForwardIterator first, ForwardIterator last, true_type)
{

}

template<class ForwardIterator, class Tp>
inline void __destroy(ForwardIterator first, ForwardIterator last, Tp*)
{
	__destroy_aux(first, last, is_trivially_constructible());
}
template<class ForwardIterator>
inline void _Destroy(ForwardIterator first, ForwardIterator last)
{
	__destroy(first, last, __VALUE_TYPE(first));
}
template<class T1, class T2>
inline void construct(T1* p, const T2& value)
{
	_Construct(p, value);
}

template<class T1>
inline void construct(T1* pointer)
{
	_Construct(pointer);
}

template<class Tp>
inline void destroy(Tp* pointer)
{
	_Destroy(pointer);
}

template<class ForwardIterator>
inline void destroy(ForwardIterator first, ForwardIterator last)
{
	_Destroy(first, last);
}
__STL_END_NAMESPACE
#endif
