#ifndef __STL_CONFIG_H__
#define __STL_CONFIG_H__

#define __STL_BEGIN_NAMESPACE namespace lsstd {
#define __STL_END_NAMESPACE }


# ifndef __STL_DEFAULT_ALLOCATOR
#   ifdef __STL_USE_STD_ALLOCATORS
#     define __STL_DEFAULT_ALLOCATOR(T) allocator< T >
#   else
#     define __STL_DEFAULT_ALLOCATOR(T) alloc
#   endif
# endif

#endif // !__STL_CONFIG_H__
