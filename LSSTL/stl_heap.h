#pragma once
#include "stl_config.h"


__STL_BEGIN_NAMESPACE

template<class RandomAccessIterator, class T, class Distance>
inline void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T value)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && *(first + parent) < value)
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = value;
}


template<class RandomAccessIterator, class Distance, class T>
void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value)
{
	Distance topIndex = holeIndex;
	Distance secondChild = 2 * (holeIndex + 1);  // ���ӽڵ�
	while (secondChild < len)
	{
		if (*(first + secondChild) < *(first + secondChild - 1))
		{
			secondChild--; // ��ڵ�����ҽڵ�
		}
		*(first + holeIndex) = *(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (holeIndex + 1);
	}
	if (secondChild == len)
	{
		// ���ֻ����ڵ㣬û���ҽڵ�
		*(first + holeIndex) = *(first + secondChild - 1);
		holeIndex = secondChild - 1;
	}
	__push_heap(first, holeIndex, topIndex, value);
}


//////////////////////////////////////////////////////////////////////////
// push heap

template<class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*)
{
	__push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
}


template<class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	__push_heap_aux(first, last, __DISTANCE_TYPE(first), __VALUE_TYPE(first));
}

//////////////////////////////////////////////////////////////////////////
// pop heap

template<class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*)
{
	*result = *first;
	__adjust_heap(first, Distance(0), Distance(last - first), value);
}

template<class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*)
{
	__pop_heap(first, last - 1, (last - 1), T(*(last - 1)), __DISTANCE_TYPE(first));
}

template<class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	__pop_heap_aux(first, last, __VALUE_TYPE(first));
}

//////////////////////////////////////////////////////////////////////////
// sort heap
template<class RandomAccessIterator>
inline void sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	while (last - first > 1)
	{
		pop_heap(first, last--);
	}
}




//////////////////////////////////////////////////////////////////////////
// make heap

template<class RandomAccessIterator, class T, class Distance>
inline void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
{
	// Ԫ�ظ���Ϊ0��1������Ҫ��������
	if (last - first < 2)
	{
		return;
	}
	Distance len = last - first;
	Distance holeIndex = (len - 2) / 2; // �ҵ����һ����Ҷ�ӽڵ�Ľڵ㣬��ΪҶ�ӽڵ㲻��Ҫadjust
	while (true)
	{
		__adjust_heap(first, holeIndex, len, *(first + holeIndex));
		if (holeIndex == 0) // ���DistanceΪ�޷�����������ôwhile(holeIndex >= 0)���ܻ�����ѭ��
			return;
		--holeIndex;
	}
}

template<class RandomAccessIterator>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	__make_heap(first, last, __VALUE_TYPE(first), __DISTANCE_TYPE(first));
}

__STL_END_NAMESPACE