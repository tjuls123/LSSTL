#pragma once
#include "stl_config.h"

__STL_BEGIN_NAMESPACE

template<class Tp, Tp Val>
struct integral_constant
{
	static constexpr Tp value = Val;
	using value_type = Tp;
	using type = integral_constant;

	constexpr operator value_type() const noexcept
	{
		return (value);
	}
};


template<bool Val>
using bool_constant = integral_constant<bool, Val>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;


//////////////////////////////////////////////////////////////////////////
template<class T, class U>
struct is_same : false_type{};

template<class T>
struct is_same <T, T> : true_type {};







/************************************************************************/
/*                           Type transformations                                           */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// remove_const
template<class T>
struct remove_const {
	using type = T;
};

template<class T>
struct remove_const<const T>
{
	using type = T;
};

template<class T>
using remove_const_t = typename remove_const<T>::type;

template<class T>
struct remove_volatile
{
	using type = T;
};


template<class T>
struct remove_volatile<volatile T>
{
	using type = T;
};

template<class T>
using remove_volatile_t = typename remove_volatile<T>::type;


template<class T>
struct remove_cv
{
	using type = T;
};

template<class T>
struct remove_cv<const T>
{
	using type = T;
};

template<class T>
struct remove_cv<volatile T>
{
	using type = T;
};

template<class T>
struct remove_cv<const volatile T>
{
	using type = T;
};

template<class T>
using remove_cv_t = typename remove_cv<T>::type;


template<class T>
struct add_const
{
	using type = const T;
};

template<class T>
using add_const_t = const T;

template<class T>
struct add_volatile
{
	using type = volatile T;
};

template<class T>
using add_volatile_t = volatile T;


template<class T>
struct add_cv
{
	using type = const volatile T;
};

template<class T>
using add_cv_t = const volatile T;


//////////////////////////////////////////////////////////////////////////
template<class T>
struct is_array : false_type {};

template<class T>
struct is_array<T[]> : true_type {};

template<class T, size_t N>
struct is_array<T[N]> : true_type {};


//////////////////////////////////////////////////////////////////////////
template<class T>
struct _is_float_point : false_type {};

template<>
struct _is_float_point<float> : true_type {};

template <>
struct _is_float_point<double> : true_type{};

// template<>
// struct _is_float_point<long float> : true_type{};

template<class T>
struct is_float_point : _is_float_point<remove_cv_t<T>>::type {};


//////////////////////////////////////////////////////////////////////////
// Is_integral

template<class T>
struct _is_integral : false_type{};

template<>
struct _is_integral<bool> : true_type {};

template<>
struct _is_integral<char> : true_type{};

template<>
struct _is_integral<unsigned char> : true_type {};

template<>
struct _is_integral<signed char> : true_type {};

template<>
struct _is_integral<short> : true_type {};

template<>
struct _is_integral<unsigned short> : true_type {};

template<>
struct _is_integral<int> : true_type {};

template<>
struct _is_integral<unsigned int> : true_type {};

template<>
struct _is_integral<long> : true_type {};

template<>
struct _is_integral<unsigned long> : true_type {};

template<>
struct _is_integral<long long> : true_type {};

template<>
struct _is_integral<unsigned long long> : true_type {};

template<class T>
struct is_integral : _is_integral<remove_cv<T>>::type {};


//////////////////////////////////////////////////////////////////////////
template<class T>
struct is_lvalue_reference : false_type{};

template<class T>
struct is_lvalue_reference<T&> : true_type {};


//////////////////////////////////////////////////////////////////////////
template<class T>
struct is_pointer : false_type{};

template<class T>
struct is_pointer<T*> : true_type {};

template<class T>
struct is_pointer<T * const> : true_type {};


template<class T>
struct is_pointer<T * volatile> : true_type {};

template<class T>
struct is_pointer<T * const volatile> : true_type {};


//////////////////////////////////////////////////////////////////////////
template<class T>
struct is_rvalue_reference : false_type{};

template<class T>
struct is_rvalue_reference<T &&> : true_type{};


//////////////////////////////////////////////////////////////////////////
template<class T>
struct is_void : false_type{};

template<>
struct is_void<void> : true_type{};





/************************************************************************/
/*        Composite type categories                                                              */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
template<class T>
struct is_arithmetic : bool_constant < is_float_point<T>::value || is_integral<T>::value > {};


// template<class T>
// struct is_fundamental : bool_constant<is_arithmetic<T>::value ||
// 	is_void<T>::value || 
// 	typename is_same<nullptr, typename remove_cv<T>::type>::value> {};

//////////////////////////////////////////////////////////////////////////
// 根据对is_const的参数进行const特化，从而判断是否为const
template<class T>
struct is_const : false_type {};

// is_const 的特化版本
template<class T>
struct is_const<const T> : true_type {};


//////////////////////////////////////////////////////////////////////////
template<class T>
struct is_volatile : false_type {};

template<class T>
struct is_volatile<const T> : true_type {};

//////////////////////////////////////////////////////////////////////////


/************************************************************************/
/*                                  Type features                                    */
/************************************************************************/

// template<class T>
// struct is_destructible : bool_constant<__is_destructible(T)> {};
// 
// template<class T, class... Args>
// struct is_trivially_constructible : bool_constant<__is_trivially_constructible(T, ...Args)> {};



template<class T>
struct type_traits
{
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = false_type;
	using has_trivial_copy_constructor = false_type;
	using has_trivial_assignment_operator = false_type;
	using has_trivial_destructor = false_type;
	using is_POD_type = false_type;
};


template<> struct type_traits<bool> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<char> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<signed char> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<unsigned char> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<short> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<unsigned short> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<int> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<unsigned int> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<long> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<unsigned long> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<long long> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<unsigned long long> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<float> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<double> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<long double> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<char*> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};

template<> struct type_traits<signed char*> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<unsigned char*> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<const char*> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<const signed char*> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};


template<> struct type_traits<const unsigned char*> {
	using this_dummy_member_must_be_first = true_type;
	using has_trivial_default_constructor = true_type;
	using has_trivial_copy_constructor = true_type;
	using has_trivial_assignment_operator = true_type;
	using has_trivial_destructor = true_type;
	using is_POD_type = true_type;
};
__STL_END_NAMESPACE
