#ifndef __LS_STL_INTERNAL_VECTOR_H
#define __LS_STL_INTERNSL_VECTOR_H

#include"stl_config.h"
#include "stl_alloc.h"
#include "stl_construct.h"
#include "stl_algobase.h"
#include "stl_uninitialized.h"
__STL_BEGIN_NAMESPACE


template<class _Tp, class _Alloc>
class _Vector_base
{
public:
	using allocator_type = typename allocator_traits<_Alloc>::allocator_type;

	allocator_type get_allocator() const { return allocator_type(); }

	_Vector_base(const allocator_type& allocator)
		: _M_start(nullptr), _M_finish(nullptr), _M_end_of_storage(nullptr)
	{
	}

	_Vector_base(size_t n, const allocator_type& allocator)
	{
		_M_start = _M_allocate(n);
		_M_finish = _M_start;
		_M_end_of_storage = _M_start + n;
	}

	~_Vector_base()
	{
		_M_deallocate(_M_start, _M_end_of_storage - _M_start);
	}

protected:
	_Tp* _M_allocate(size_t n)
	{
		return allocator_type().allocate(n);
	}
	void _M_deallocate(_Tp* pointer, size_t n)
	{
		allocator_type().deallocate(pointer, n);
	}

protected:
	_Tp* _M_start;
	_Tp* _M_finish;
	_Tp* _M_end_of_storage;
};



template<class _Tp, class _Alloc = allocator<_Tp>>
class vector : protected _Vector_base<_Tp, _Alloc>
{
private:
	using _Base = _Vector_base<_Tp, _Alloc>;

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

	//typedef reverse_iterator<const_iterator, value_type, const_reference, difference_type> const_reverse_iterator;
	//typedef reverse_iterator<iterator, value_type, reference, difference_type> reverse_iterator;

protected:
	using _Base::_M_start;
	using _Base::_M_finish;
	using _Base::_M_end_of_storage;
	using _Base::_M_allocate;
	using _Base::_M_deallocate;

protected:
	void _M_insert_aux(iterator position, const _Tp& x);
	void _M_insert_aux(iterator position);

public:
	iterator begin() { return _M_start; }
	const_iterator cbegin() const { return _M_start; }
	iterator end() { return _M_finish; }
	const_iterator cend() const{ return _M_finish; }

	//reverse_iterator rbegin() { return reverse_iterator(end()); }
	//const_reverse_iterator crbegin() cosnt { return const_reverse_iterator(cend()); }
	//reverse_iterator rend() { return reverse_iterator(begin()); }
	//const_reverse_iterator crend() const { return const_reverse_iterator(cbegin()); }

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
		: _Base(n, allocator)
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
	//vector<_Tp, _Alloc>& operator=(const vector<_Tp, _Alloc>& other);

	/***************************public function**********************************/
	void reserve(size_type n)
	{
		if (capacity() < n)
		{
			const size_type old_size = size();
			iterator tmp = _M_allocate_and_copy(n, _M_start, _M_finish);
			destroy(_M_start, _M_finish);
			_M_deallocate(_M_start, _M_end_of_storage - _M_start);
			_M_start = tmp;
			_M_finish = _M_start + old_size;
			_M_end_of_storage = _M_start + n;
		}
	}

	iterator _M_allocate_and_copy(size_type n, const_iterator firt, const_iterator last)
	{
		iterator result = _M_allocate(n);
		uninitialized_copy(firt, last, result);
		return result;
	}
	void assign(size_type n, const _Tp& val) { _M_fill_assign(n, val); }
	reference front() { return *begin(); }
	const_reference front() const { return *cbegin(); }
	reference back() { return *(end() - 1); }
	const_reference back() const { return *(cend() - 1); }

	void push_back(const _Tp& value)
	{
		if (_M_finish != _M_end_of_storage)
		{
			construct(_M_finish, value);
			++_M_finish;
		 }
		else
		{
			_M_insert_aux(end(), value);
		}
	}
	void push_back()
	{
		if (_M_finish != _M_end_of_storage)
		{
			construct(_M_finish);
			++_M_finish;
		}
		else
		{
			_M_insert_aux(end());
		}
	}

	void swap(vector<_Tp, _Alloc>& other)
	{
		lsstd::swap(_M_start, other._M_start);
		lsstd::swap(_M_finish, other._M_finish);
		lsstd::swap(_M_end_of_storage, other._M_end_of_storage);
	}
	iterator insert(iterator position, const _Tp& value)
	{
		size_type n = position - begin();
		if (_M_finish != _M_end_of_storage && position == end())
		{
			construct(_M_finish, value);
			++_M_finish;
		}
		else
		{
			_M_insert_aux(position, value);
		}
		return begin() + n;
	}
	iterator insert(iterator position)
	{
		size_type n = position - begin();
		if (_M_finish != _M_end_of_storage && position == end())
		{
			construct(_M_finish);
			++_M_finish;
		}
		else
		{
			_M_insert_aux(position);
		}
		return begin() + n;
	}

	void insert(iterator position, size_type n, const _Tp& value)
	{
		_M_fill_insert(position, n, value);
	}
	

	void pop_back()
	{
		--_M_finish;
		destroy(_M_finish);
	}

	iterator erase(iterator position)
	{
		if (position + 1 != end())
		{
			copy(position + 1, _M_finish, position);
		}
		--_M_finish;
		destroy(_M_finish);
		return position;
	}
	iterator erase(iterator first, iterator last)
	{
		iterator iter = copy(last, _M_finish, first);
		destroy(iter, _M_finish);
		_M_finish = _M_finish - (last - first);
	}
	void resize(size_type new_sieze, const _Tp& value)
	{
		if (new_sieze < size())
		{
			erase(begin() + new_sieze, end());
		}
		else
		{
			insert(end(), new_sieze - size(), value);
		}
	}
	void resize(size_type new_sieze)
	{
		resize(new_sieze, _Tp());
	}
	void clear() { erase(begin(), end()); }

protected:
	void _M_insert(iterator position, size_type n, const _Tp& value);
	void _M_fill_assign(size_type n, const _Tp& val);
	void _M_fill_insert(iterator position, size_type n, const _Tp& value);
};

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_insert_aux(iterator position, const _Tp& x)
{
	if (_M_finish != _M_end_of_storage)
	{
		construct(_M_finish, *(_M_finish - 1));
		++_M_finish;
		copy_backward(position, _M_finish - 2, _M_finish - 1);
		*position = x;
	}
	else
	{
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		iterator new_start = get_allocator().allocate(len);
		iterator new_finish = new_start;

		new_finish = uninitialized_copy(_M_start, position, new_start);
		construct(new_finish, x);
		++new_finish;
		new_finish = uninitialized_copy(position, _M_finish, new_finish);

		destroy(begin(), end());
		get_allocator().deallocate(_M_start, _M_end_of_storage - _M_start);
		_M_start = new_start;
		_M_finish = new_finish;
		_M_end_of_storage = _M_start + len;

	}
}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_insert_aux(iterator position)
{
	if (_M_finish != _M_end_of_storage)
	{
		construct(_M_finish, *(_M_finish - 1));
		++_M_finish;
		copy_backward(position, _M_finish - 2, _M_finish - 1);
		*position = _Tp();
	}
	else
	{
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		iterator new_start = _M_allocate(len);
		iterator new_finish = new_start;

		new_finish = uninitialized_copy(_M_start, position, new_start);
		construct(new_finish);
		++new_finish;
		new_finish = uninitialized_copy(position, _M_finish, new_finish);

		destroy(begin(), end());
		_M_deallocate(_M_start, _M_end_of_storage - _M_start);
		_M_start = new_start;
		_M_finish = new_finish;
		_M_end_of_storage = _M_start + len;
	}
}
template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_insert(iterator position, size_type n, const _Tp& value)
{

}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_assign(size_type n, const _Tp& val)
{

}

template<class _Tp, class _Alloc>
void vector<_Tp, _Alloc>::_M_fill_insert(iterator position, size_type n, const _Tp& value)
{
	if (n != 0)
	{
		if (size_type(_M_end_of_storage - _M_finish) >= n)
		{
			_Tp value_copy = value;
			const size_type element_after = _M_finish - position;
			iterator old_finish = _M_finish;
			if (element_after > n)
			{
				uninitialized_copy(_M_finish - n, _M_finish, _M_finish);
				_M_finish += n;
				copy_backward(position, old_finish - n, old_finish);
				fill(position, position + n, value_copy);
			}
			else
			{
				uninitialized_fill_n(_M_finish, n - element_after, value_copy);
				_M_finish += n - element_after;
				uninitialized_copy(position, old_finish, _M_finish);
				_M_finish += element_after;
				fill(position, old_finish, value_copy);
			}
		}
		else
		{
			const size_type old_size = size();
			const size_type len = old_size + max(old_size, n);
			iterator new_start = _M_allocate(len);
			iterator new_finish = new_start;
			new_finish = uninitialized_copy(_M_start, position, new_start);
			new_finish = uninitialized_fill_n(new_finish, n, value);
			new_finish = uninitialized_copy(position, _M_finish, new_finish);

			destroy(_M_start, _M_finish);
			_M_deallocate(_M_start, _M_end_of_storage - _M_start);
			_M_start = new_start;
			_M_finish = new_finish;
			_M_end_of_storage = new_start + len;
		}
	}
}

__STL_END_NAMESPACE

#endif
