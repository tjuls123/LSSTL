#ifndef __LS_STL_INTERNAL_VECTOR_H
#define __LS_STL_INTERNSL_VECTOR_H

#include"stl_config.h"

__STL_BEGIN_NAMESPACE

template<class _Tp, class _Allocator, bool _IsStatic>
class  _Vector_alloc_base
{
public:
	typedef typename _Alloc_traits<_Tp, _Allocator>::allocator_type allocator_type;

	allocator_type get_allocator() const {return allocator_type();}

	_Vector_alloc_base(const allocator_type& allocator)
		:_M_start(0), _M_finish(0), _M_end_of_storage(0)
	{
	}
protected:
	_Tp* _M_start;
	_Tp* _M_finish;
	_TP* _M_end_of_storage;

	typedef typename _Alloc_traits<_Tp, _Allocator>::_Alloc_type _Alloc_type;

	_Tp* _M_allocate(size_t n)
	{
		return _Alloc_type::allocate(n);
	}
	void _M_deallocate(_Tp* pointer, size_t n)
	{
		_Alloc_type::deallocate(pointer, n);
	}
};


template<class _Tp, class _Alloc>
class _Vector_base : public _Vector_alloc_base<_Tp, _Alloc, _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
{
public:
	typedef _Vectator_alloc_base<_Tp, _Alloc, _Alloc_traits<_Tp, _Alloc>::_S_instanceless> _Base;

	typedef typename _Base::allocator_type allocator_type;

	_Vector_base(const allocator_type& allocator)
		: _Base(a)
	{
	}

	_Vector_base(size_t n, const allocator_type& allocator)
		: _Base(allocator)
	{
		_M_start = _M_allocate(n);
		_M_finish = _M_start;
		_M_end_of_storage = _M_start + n;
	}

	~_Vector_base()
	{
		_m_deallocate(_M_start, _M_end_of_storage - _M_start);
	}
};



template<class _Tp, class _Alloc = allocator<_Tp>>
class vector : protected _Vector_base
{
private:
	typedef _Vector_base _Base;

public:
	typedef _Tp value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type* iterator;
	typedef const value_type* const_iterator;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef typename _Base::allocator_type allocator_type;
	allocator_type get_allocator() const { return _Base::get_allocator(); }

	typedef reverse_iterator<const_iterator, value_type, const_reference, difference_type> const_reverse_iterator;
	typedef reverse_iterator<iterator, value_type, reference, difference_type> reverse_iterator;

protected:
	using _Base::_M_allocate;
	using _Base::_M_deallocate;
	using _Base::_M_start;
	using _Base::_M_finish;
	using _Base::_M_end_of_storage;

protected:
	void _M_insert_aux(iterator position, const _Tp& x);
	void _M_insert_aus(iterator position);

public:
	iterator begin() { return _M_start; }
	const_iterator cbegin() const { return _M_start; }
	iterator end() { return _M_finish; }
	cosnt_iterator cend() const{ return _M_finish; }

	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator crbegin() cosnt { return const_reverse_iterator(cend()); }
	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

	size_type size() const { return size_type(cend() - cbegin()); }
	size_type max_size() const { return size_type(-1) / sizeof(value_type); }
	size_type capacity() const { return size_type(_M_end_of_storage - cbegin()); }
	bool empty() const { return cbegin() == cend(); }

	reference operator[] (size_type index) { return *(begin() + index); }
	const_reference operator[] (size_type index) const { return *(cbegin() + index); }

	/***************begin vector constructor****************/
	explicit vector(const allocator_type& allocator = allocator_type())
		: _Base(allocator) {}
	
	vector(size_type n, const _Tp& value, const allocator_type& allocator = allocator_type())
		: _Base(n, a)
	{
		_M_finish = uninitialized_fill_n(_M_start, n, value);
	}

	explicit vector(size_type n)
		:_Base(n, allocator_type())
	{
		_M_finish = uninitialized_fill_n(_M_start, n, _Tp());
	}
	explicit vector(const vector<_Tp, _Alloc>& other)
		:_Base(other.size(), other.get_allocator())
	{
		_M_finish = uninitialized_copy(other.begin(), other.end(), _M_start);
	}

	~vector() { destroy(_M_start, _M_finish); }

	/*************************operator******************************/
	vector<_Tp, _Alloc>& operator=(const vector<_Tp, _Alloc>& other);

	/***************************public function**********************************/
	void reserve(size_type n);
	void assign(size_type n, const _Tp& val) { _M_fill_assign(n, val); }
	reference front() { return *begin(); }
	const_reference front() const { return *cbegin(); }
	reference back() { return *(end() - 1); }
	const_reference back const() { return *(cend() - 1); }

	void push_back(const _Tp& value);
	void push_back();

	void swap(vector<_Tp, _Alloc>& other)
	{

	}
	iterator insert(iterator position, const _Tp& value);
	iterator insert(iterator position);

	void insert(iterator position, size_type n, const _Tp& value);

	

	void pop_back();

	iterator erase(iterator position);
	iterator erase(iterator first, iterator end);
	void resize(size_type n, const _Tp& value);
	void resize(size_type n);
	void clear() { erase(begin(), end()); }

protected:
	void _M_insert(iterator position, s ize_type n, const _Tp& value);
	void _M_fill_assign(size_type n, const _Tp& val);
};

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
void vector<_Tp, _Alloc>::resize(size_type n)
{

}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
void vector<_Tp, _Alloc>::resize(size_type n, const _Tp& value)
{

}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::erase(iterator first, iterator end)
{
	return first;
}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::erase(iterator position)
{
	return first;
}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
void vector<_Tp, _Alloc>::pop_back()
{

}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
void vector<_Tp, _Alloc>::insert(iterator position, size_type n, const _Tp& value)
{

}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::insert(iterator position)
{
	return position;
}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
typename vector<_Tp, _Alloc>::iterator vector<_Tp, _Alloc>::insert(iterator position, const _Tp& value)
{
	return position;
}

template<class _Tp, class _Alloc /*= __STL_DEFAULT_ALLOCATOR(_Tp)*/>
void vector<_Tp, _Alloc>::_M_fill_assign(size_type n, const _Tp& val)
{

}

template<class _Tp, class _Alloc>
inline bool operator==(vector<_Tp, _Alloc> vec1, vector<_Tp, _Alloc> vec2)
{
	return vec1.size() == vec2.size() && equal(vec1.begin(), vec1.end(), vec2.begin());
}

template<class _Tp, class _Alloc>
vector<_Tp, _Alloc>& vector<_Tp, _Alloc>::operator=(const vector < _Tp, _Alloc& x)
{
	return *this;
}


template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::reserve(size_type n)
{
	if (capacity() < n)
	{
		const size_type old_size = size();
		iterator tmp = _M_allocate_and_copy(n, _M_start, _M_finish);
		 (_M_start, _M_end_of_storage - _M_start);
		_M_start = tmp;
		_M_finish = tmp + old_size;
		_M_end_of_storage = _M_start + n;
	}
}


template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::push_back(const _Tp& value)
{
	if (_M_finish != _M_end_of_storage)
	{
		construct(_M_finish, value);
		++_M_finish;
	}
	else
	{

	}
}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::push_back()
{

}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_insert_aus(iterator position, const _Tp& val)
{
	if (_M_finish != _M_end_of_storage)
	{
		construct(_M_finish, )
	}
}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_insert_aus(iterator position)
{
	if (_M_finish != _M_end_of_storage)
	{
		construct(_M_finish, )
	}
}

__STL_END_NAMESPACE

#endif
