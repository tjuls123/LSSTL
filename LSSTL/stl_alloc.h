#ifndef __LS_STL_INTERNAL_ALLOC_H__
#define __LS_STL_INTERNAL_ALLOC_H__

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
		return n > 0 ? ::operator new(n) : nullptr;
	}
	void deallocate(pointer p, size_type n)
	{
		::operator delete p;
	}
	void deallocate(pointer p)
	{
		::operator delete p;
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

#endif // !__LS_STL_INTERNAL_ALLOC_H__
