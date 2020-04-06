#pragma once
#include "stl_config.h"

__STL_BEGIN_NAMESPACE

template<class Container>
class back_insert_iterator
{
protected:
	Container *container;
public:
	using container_type = Container;
	using iterator_category = output_iterator_tag;
	using value_type = void;
	using difference_type = void;
	using pointer = void;
	using reference = void;

	explicit back_insert_iterator(Container& c)
		: container(&c)
	{
	}
	back_insert_iterator& operator=(const typename Container::value_type& value)
	{
		container->push_back(value);
		return *this;
	}
	back_insert_iterator& operator*() { return *this; }
	back_insert_iterator& operator++() { return *this; }
	back_insert_iterator& operator++(int) { return *this; }
};

template<class Container>
inline back_insert_iterator< Container> back_inserter(Container& Cont)
{
	return back_insert_iterator<Container>(Cont);
}


template<class Container>
class front_insert_iterator
{
protected:
	Container* container;
public:
	using container_type = Container;
	using iterator_category = output_iterator_tag;
	using value_type = void;
	using difference_type = void;
	using pointer = void;
	using reference = void;

	explicit front_insert_iterator(Container &cont)
		: container(&cont) {}

	front_insert_iterator&operator=(const typename Container::value_type& value)
	{
		container->push_front(value);
		return *this;
	}

	front_insert_iterator& operator*() { return *this; }
	front_insert_iterator& operator++() { return *this; }
	front_insert_iterator& operator++(int) { return *this; }
};


template<class Container>
inline front_insert_iterator< Container> front_inserter(Container& Cont)
{
	return front_insert_iterator< Container>(Cont);
}



template<class Container>
class insert_iterator
{
protected:
	Container* container;
	typename Container::iterator iter;
public:
	using container_type = Container;
	using iterator_category = output_iterator_tag;
	using value_type = void;
	using difference_type = void;
	using pointer = void;
	using reference = void;

	explicit insert_iterator(Container &cont, typename Container::iterator _iter)
		: container(&cont), iter(_iter){}

	insert_iterator&operator=(const typename Container::value_type& value)
	{
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}

	insert_iterator& operator*() { return *this; }
	insert_iterator& operator++() { return *this; }
	insert_iterator& operator++(int) { return *this; }
};


template<class Container, class Iterator>
inline insert_iterator< Container> inserter(Container& Cont, Iterator iter)
{
	return insert_iterator< Container>(Cont, iter);
}




__STL_END_NAMESPACE