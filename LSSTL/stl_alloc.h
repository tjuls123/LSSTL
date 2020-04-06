#ifndef __LS_STL_INTERNAL_ALLOC_H__
#define __LS_STL_INTERNAL_ALLOC_H__

__STL_BEGIN_NAMESPACE

template<class _Alloc>
struct allocator_traits
{
	using allocator_type = _Alloc;
	using value_type = typename allocator_type::value_type;
	using pointer = typename allocator_type::pointer;
	using const_pointer = typename allocator_type::const_pointer;
	//using void_pointer = ;
	using difference_type = typename allocator_type::difference_type;
	using size_type = typename allocator_type::size_type;

};
template<class _Tp>
class allocator
{
public:
	using size_type = size_t;
	using difference_type = ptrdiff_t;
	using pointer = _Tp * ;
	using const_pointer = const _Tp*;
	using reference = _Tp & ;
	using const_reference = const _Tp&;
	using value_type = _Tp;
	
	template<class Tp1>
	struct rebind
	{
		using other = allocator<Tp1>;
	};
	//
	allocator() noexcept {}
	allocator(const allocator&) noexcept {}
	template<class _Tp1>
	allocator(const allocator<_Tp1>&) noexcept {}
	~allocator() noexcept {}

	pointer address(reference x) const { return &x; }
	const_pointer address(const_reference x) const { return &x; }

	_Tp* allocate(size_type n)
	{
		return n > 0 ? static_cast<_Tp*>(::operator new(n * sizeof(_Tp))) : nullptr;
	}
	void deallocate(pointer p, size_type n)
	{
		deallocate(p);
	}
	void deallocate(pointer p)
	{
		::operator delete (p);
	}
	size_type max_size() const noexcept
	{
		return size_t(-1) / sizeof(_Tp);
	}
	void construct(pointer p, const _Tp& val)
	{
		new(p) _Tp(val); // placement new
	}
	void destroy(pointer p)
	{
		p ->~_Tp();  // call destructor
	}
};



template<>
class allocator<void>
{
public:
	using value_type = void;
	using pointer = void *;
	using const_pointer = const void*;

	template<class U>
	struct rebind
	{
		using other = allocator<U>;
	};
};


template<class T, class U>
inline bool operator == (const allocator<T>& alloc, const allocator<U>& other_alloc)
{
	return true;
}

template<class T, class U>
inline bool operator != (const allocator<T>& alloc, const allocator<U>& other_alloc)
{
	return false;
}

__STL_END_NAMESPACE

#endif // !__LS_STL_INTERNAL_ALLOC_H__
