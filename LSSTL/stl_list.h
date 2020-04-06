#pragma once
#include "stl_config.h"
#include "stl_alloc.h"
#include "stl_iterator_base.h"


__STL_BEGIN_NAMESPACE

struct list_node_base
{
	list_node_base* next;
	list_node_base* prev;
};

template<class T>
struct list_node : public list_node_base
{
	T data;
};



//////////////////////////////////////////////////////////////////////////
// list iterator
struct list_iterator_base
{
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using iterator_category = bidirectional_iterator_tag;

	list_node_base* m_node;

	list_iterator_base(list_node_base* node) : m_node(node) {}
	list_iterator_base() : m_node(nullptr) {}

	void increase() { m_node = m_node->next; }
	void decrease() { m_node = m_node->prev; }

	bool operator==(const list_iterator_base& other) const
	{
		return m_node == other.m_node;
	}
	bool operator != (const list_iterator_base& other) const
	{
		return m_node != other.m_node;
	}

};

template<class T, class Ref, class Ptr>
struct list_iterator : public list_iterator_base
{
	using iterator = list_iterator<T, T&, T*>;
	using const_iterator = list_iterator<T, const T&, const T*>;
	using _Self = list_iterator<T, Ref, Ptr>;

	using value_type = T;
	using pointer = Ptr;
	using reference = Ref;
	using _Node = list_node<T>;

	list_iterator(_Node* node) : list_iterator_base(node) {}
	list_iterator() {}
	list_iterator(const list_iterator& other) :list_iterator_base(other.m_node) {}

	reference operator*() { return static_cast<_Node*>(m_node)->data; }

	// ++iter
	_Self& operator++()
	{
		this->increase();
		return *this;
	}

	// iter++
	_Self operator++(int)
	{
		_Self tmp = *this;
		this->increase();
		return tmp;
	}

	// --iter
	_Self& operator--()
	{
		this->decrease();
		return *this;
	}

	// iter--
	_Self operator--(int)
	{
		_Self tmp = *this;
		this->decrease();
		return tmp;
	}
};

template<class T, class Alloc>
class list_alloc_base
{
public:
	using allocator_type = typename allocator_traits<Alloc>::allocator_type;
	allocator_type get_allocator() const { return m_node_allocator; }
	list_alloc_base(const allocator_type& a) : m_node_allocator(a){}

protected:

	list_node<T>* get_node()
	{
		return m_node_allocator.allocate(1);
	}
	void put_node(list_node<T>* node)
	{
		m_node_allocator.deallocate(node, 1);
	}
protected:
	typename allocator_traits<Alloc>::allocator_type m_node_allocator;
	list_node<T>* m_node;
};

template<class T, class Alloc>
class list_base : public list_alloc_base<T, Alloc>
{
public:
	using Base = list_alloc_base<T, Alloc>;
	using allocator_type = Base::allocator_type;
	using Base::get_node;
	using Base::put_node;
	using Base::m_node;

	list_base(const allocator_type& a)
		: Base(a)
	{
		m_node = get_node();
		m_node->next = m_node;
		m_node->prev = m_node;
	}
	~list_base()
	{
		clear();
		put_node(m_node);
	}
	void clear()
	{
		list_node<T>* cur_node = static_cast<list_node<T>*>(m_node->next);
		while (cur_node != m_node)
		{
			list_node<T>* temp = cur_node;
			cur_node = static_cast<list_node<T>*>(cur_node->next);
			destroy(&temp->data);
			put_node(temp);
		}
		m_node->next = m_node;
		m_node->prev = m_node;
	}
};

template<class T, class Alloc = allocator<list_node<T>>>
class list : public list_base<T, Alloc>
{
private:
	using Base = list_base<T, Alloc>;
	using Base::get_node;
	using Base::put_node;
	using Base::m_node;
public:
	using value_type = T;
	using pointer = T * ;
	using const_pointer = const T*;
	using reference = T & ;
	using const_reference = const T&;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using allocator_type = typename Base::allocator_type;
	allocator_type get_allocator() const {
		return Base::get_allocator();
	}
protected:
	using Node = list_node<T>;

public:
	using iterator = list_iterator<T, T&, T*>;
	using const_iterator = list_iterator<T, const T&, const T*>;

protected:
	Node* create_node(const T& value)
	{
		Node *node = get_node();
		construct(&node->data, value);
		return node;
	}
	Node* create_node()
	{
		Node* node = get_node();
		construct(&node->data);
		return node;
	}
public:
	explicit list(const allocator_type& a = allocator_type()) : Base(a) {}
	list(size_type new_size, const T& val, const allocator_type& a = allocator_type())
		: Base(a)
	{
		insert(begin(), new_size, val);
	}
	explicit list(size_type new_size)
		: Base(allocator_type())
	{
		insert(begin(), new_size, T());
	}
	list(const list<T, Alloc>& other)
		: Base(other.get_allocator())
	{
		insert(begin(), other.begin(), other.end());
	}
	
	list(const_iterator first, const_iterator last, const allocator_type& a = allocator_type())
		: Base(a)
	{
		insert(begin(), first, last);
	}
	~list(){}

	list<T, Alloc>& operator=(const list<T, Alloc>& other);

	//////////////////////////////////////////////////////////////////////////
	//Iterators
    iterator begin() {return iterator(static_cast<Node*>(m_node->next));}
	const_iterator cbegin() const{ return static_cast<const_iterator>(m_node->next); }

	iterator end() { return static_cast<iterator>(m_node); }
	const_iterator cend() const { return static_cast<const_iterator>(m_node); }

	//////////////////////////////////////////////////////////////////////////
	// Capacity:
	bool empty() const { return m_node->next == m_node; }
	size_type size() 
	{ 
		size_type n = 0; 
		distance(cbegin(), cend(), n);
		return n;
	}
	size_type max_size() const { return size_type(-1); }

	//////////////////////////////////////////////////////////////////////////
	//Element access:
	reference front() { return *begin(); }
	const_reference front() const{ return *begin(); }

	reference back() { return *(--end()); }
	const_reference back() const { return *(--end()); }

	//////////////////////////////////////////////////////////////////////////
	//Modifiers:
	void swap(list<T, Alloc> &other)
	{
		lsstd::swap(m_node, other.m_node);
	}

	iterator insert(iterator position, const T& val)
	{
		Node* new_node = get_node();
		construct(&new_node->data, val);
		new_node->next = position.m_node;
		new_node->prev = position.m_node->prev;
		position.m_node->prev->next = new_node;
		position.m_node->prev = new_node;
		return new_node;
	}

	void insert(iterator position, size_type n, const T& val)
	{
		fill_insert(position, n, val);
	}
	template<class InputIterator>
	void insert(iterator position, InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			insert(position, *first);
			++first;
		}
	}
	void push_front(const T& val)
	{
		insert(begin(), val);
	}
	void push_back(const T& val)
	{
		insert(end(), val);
	}
	iterator erase(iterator position)
	{
		Node* next_node = position.m_node->next;
		Node* prev_node = position.m_node->prev;

		prev_node->next = next_node;
		next_node->prev = prev_node;

		Node* current_node = static_cast<Node*>(position.m_node);
		destroy(&current_node->data);
		put_node(current_node);
		return iterator(static_cast<Node*>(next_node));
	}

	iterator erase(iterator first, iterator last);
	void clear() { Base::clear(); }

	void resize(size_type new_size, const T& val)
	{
		iterator iter = begin();
		size_type len = 0;
		for (; iter != end() && len < new_size; ++iter, ++len);
		if (len == new_size)
		{
			erase(iter, end());
		}
		else
		{
			insert(end(), new_size - len, val);
		}
	}
	void resize(size_type new_size) { this->resize(new_size, T()); }

	void pop_front() { erase(begin()); }
	void pop_back() 
	{ 
		iterator tmp = end();
		erase(--tmp);
	}
	void assign(size_type n, const T& val)
	{
		fill_assign(n, val);
	}

	//////////////////////////////////////////////////////////////////////////
	//Operations
	void remove(const T& val);
	void unique();
	void merge(list& other);
// 	void reverse();
// 	void sort();

protected:
	void fill_assign(size_type n, const T& val);
	void fill_insert(iterator position, size_type n, const T& val);

};


template<class T, class Alloc>
typename list<T, Alloc>::iterator list<T, Alloc>::erase(
	iterator first, 
	iterator last)
{
	while (first != last)
	{
		erase(first++);
	}
	return last;
}

template<class T, class Alloc>
list<T, Alloc>& list<T, Alloc>::operator=(const list<T, Alloc>& other)
{
	if (this != &other)
	{
		iterator first1 = begin();
		iterator last1 = end();

		const_iterator first2 = other.cbegin();
		const_iterator last2 = other.cend();

		while (first1 != last1 && first2 != last2)
		{
			*first1++ = *first2++;
		}
		if (first2 == last2)
		{
			erase(first1, last1);
		}
		else
		{
			insert(last1, first2, last2);
		}
	}
	return *this;
}

template<class T, class Alloc>
void list<T, Alloc>::fill_assign(size_type n, const T& val)
{
	iterator iter = begin();
	for (; iter != end() && n > 0; ++iter, --n)
	{
		*iter = val;
	}
	if (n > 0)
	{
		insert(end(), n, val);
	}
	else
	{
		erase(iter, end());
	}
}

template<class T, class Alloc>
void list<T, Alloc>::fill_insert(iterator position, size_type n, const T& val)
{
	while (n--)
	{
		insert(position, val);
	}
}

template<class T, class Alloc>
void list<T, Alloc>::remove(const T& val)
{
	iterator first = begin();
	iterator last = end();
	while (first != last)
	{
		iterator next = first;
		++next;
		if (*first == val)
		{
			erase(first);
		}
		first = next;
	}
}

template<class T, class Alloc>
void list<T, Alloc>::unique()
{
	iterator first = begin();
	iterator last = end();
	if (first == last)
	{
		return;
	}
	iterator next = first;
	while (++next != last)
	{
		if (*first == *next)
		{
			erase(next);
		}
		else
		{
			first = next;
		}
		next = first;
	}
}

template<class T, class Alloc>
void list<T, Alloc>::merge(list<T, Alloc>& other)
{
	iterator first1 = begin();
	iterator last1 = end();

	const_iterator first2 = other.cbegin();
	const_iterator last2 = other.cend();
	while(first1 != last1 && first2 != last2)
	{
		if (*first1 <= *first2)
		{
			++first1;
		}
		else 
		{
			first1 = insert(first1, *first2);
			++first2;
		}
	}
	if (first2 != last2)
	{
		//insert(last1, )
	}
}

__STL_END_NAMESPACE