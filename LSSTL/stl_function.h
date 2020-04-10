#pragma once
#include "stl_config.h"

__STL_BEGIN_NAMESPACE

template<class Arg, class Result>
struct unary_function
{
	using argument_type = Arg;
	using result_type = Result;
};

template<class Arg1, class Arg2, class Result>
struct binary_function
{
	using first_argument_type = Arg1;
	using second_argument_type = Arg2;
	using result_type = Result;
};


template<class T>
struct plus : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	{
		return x + y;
	}
};


template<class T>
struct minus : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	{
		return x - y;
	}
};


template<class T>
struct multiplies : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	{
		return x * y;
	}
};


template<class T>
struct divides : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	{
		return x / y;
	}
};


template<class T>
struct modulus : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	{
		return x % y;
	}
};


//////////////////////////////////////////////////////////////////////////
// ±È½Ï
template<class T>
struct equal_to : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x == y;
	}
};


template<class T>
struct not_equal_to : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x != y;
	}
};


template<class T>
struct greater : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x > y;
	}
};


template<class T>
struct less : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x < y;
	}
};


template<class T>
struct greater_equal : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x >= y;
	}
};


template<class T>
struct less_equal : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x <= y;
	}
};


template<class T>
struct logic_and : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x && y;
	}
};


template<class T>
struct logic_or : public binary_function<T, T, bool>
{
	bool operator()(const T& x, const T& y)
	{
		return x || y;
	}
};


template<class T>
struct logic_not : public unary_function<T, bool>
{
	bool operator()(const T& x)
	{
		return !x;
	}
};


template<class T>
struct hash : public unary_function<T, T>
{
	T operator()(const T& x)
	{
		return x;
	}
};


template<class T>
struct identity : public unary_function<T, T>
{
	T operator()(const T& x)
	{
		return x;
	}
};

__STL_END_NAMESPACE