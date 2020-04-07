#pragma once
#include "stl_config.h"
#include "stl_alloc.h"
#include <xutility>


__STL_BEGIN_NAMESPACE

template <class Value>
struct hashtable_node
{
	hashtable_node* next;
	Value val;
};


// 申明hashtable
template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
class hashtable;

template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
struct hashtable_iterator;

template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
struct hashtable_const_iterator;

template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
struct hashtable_iterator
{
	// 标准接口
	using iterator = hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;
	using const_iterator = hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;
	using iterator_category = forward_iterator_tag;
	using value_type = Value;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
	using reference = Value & ;
	using pointer = Value * ;

	using _Hashtable = hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;
	using _Node = hashtable_node<Value>;

	_Node* cur_node;
	_Hashtable *ht;

	hashtable_iterator(_Node* node, _Hashtable in_ht)
		: cur_node(node), ht(in_ht) {}

	hashtable_iterator() 
		: cur_node(nullptr), ht(nullptr) {}

	reference operator*()const { return cur_node->val; }
	pointer operator->() const { return &cur_node->val; }

	iterator& operator++();
	iterator operator++(int);

	bool operator==(const iterator& other) const
	{
		return cur_node == other.cur_node;
	}
	bool operator != (const iterator& other) const
	{
		return cur_node != other.cur_node;
	}
};


template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
struct hashtable_conster_iterator
{
	// 标准接口
	using iterator = hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;
	using const_iterator = hashtable_const_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;
	using iterator_category = forward_iterator_tag;
	using value_type = Value;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
	using reference = const Value & ;
	using pointer = const Value * ;

	using _Hashtable = hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;
	using _Node = hashtable_node<Value>;

	_Node* cur_node;
	_Hashtable *ht;

	hashtable_conster_iterator(_Node* node, _Hashtable in_ht)
		: cur_node(node), ht(in_ht) {}

	hashtable_conster_iterator()
		: cur_node(nullptr), ht(nullptr) {}

	reference operator*()const { return cur_node->val; }
	pointer operator->() const { return &cur_node->val; }

	hashtable_conster_iterator& operator++();
	hashtable_conster_iterator operator++(int);

	bool operator==(const hashtable_conster_iterator& other) const
	{
		return cur_node == other.cur_node;
	}
	bool operator != (const hashtable_conster_iterator& other) const
	{
		return cur_node != other.cur_node;
	}
};


enum
{
	__stl_num_primes = 28
};


static const unsigned long __stl_prime_list[__stl_num_primes] =
{
  53ul,         97ul,         193ul,       389ul,       769ul,
  1543ul,       3079ul,       6151ul,      12289ul,     24593ul,
  49157ul,      98317ul,      196613ul,    393241ul,    786433ul,
  1572869ul,    3145739ul,    6291469ul,   12582917ul,  25165843ul,
  50331653ul,   100663319ul,  201326611ul, 402653189ul, 805306457ul,
  1610612741ul, 3221225473ul, 4294967291ul
};


inline unsigned long __stl_next_prime(unsigned long __n)
{
	const unsigned long* __first = __stl_prime_list;
	const unsigned long* __last = __stl_prime_list + (int)__stl_num_primes;
	const unsigned long* pos = lower_bound(__first, __last, __n);
	return pos == __last ? *(__last - 1) : *pos;
}


template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
class hashtable;


template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
bool operator==(
	const hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&ht1, 
	const hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>& ht2);




template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
public:
	using key_type = Key;
	using value_type = Value;
	using hasher = HashFun;
	using key_equal = EqualKey;

	using value_type = Value;
	using difference_type = ptrdiff_t;
	using size_type = size_t;
	using reference = value_type & ;
	using const_reference = const value_type &;
	using const_pointer = const value_type *;
	using pointer = value_type * ;

	hasher hash_funct() const { return hash; }
	key_equal key_eq() const { return equals; }

public:
	using allocator_type = typename allocator_traits<Alloc>::allocator_type;
	allocator_type get_allocator() const {
		return node_allocator;
	}
private:
	typename allocator_traits<Alloc>::allocator_type node_allocator;
	_Node* get_node() { return node_allocator.allocate(1); }
	void put_node(_Node* p) { node_allocator.deallocate(p, 1); }

private:
	using _Node = hashtable_node<value_type>;

	hasher hash;
	key_equal equals;
	ExtractKey get_key;
	vector<_Node*, Alloc> buckets;
	size_type num_element;

public:
	using iterator = hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;
	using const_iterator = hashtable_conster_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>;

	friend struct iterator;
	friend struct const_iterator;

public:
	hashtable(size_type size, 
		const HashFun& in_hf, 
		const EqualKey& in_equal_key,
		const ExtractKey& in_extract_key,
		const allocator_type& a = allocator_type())
		: node_allocator(a), hash(in_hf), equals(in_equal_key), get_key(in_extract_key), buckets(a), num_element(0)
	{
	}

	hashtable(size_type size,
		const HashFun& in_hf,
		const EqualKey& in_equal_key,
		const allocator_type& a = allocator_type())
		: node_allocator(a), hash(in_hf), equals(in_equal_key), get_key(ExtractKey()), buckets(a), num_element(0)
	{
	}

	hashtable(const hashtable& other)
		: node_allocator(other.get_allocator()), 
		hash(other.hash), 
		equals(other.equals), 
		get_key(other.get_key),
		buckets(other.get_allocator()), 
		num_element(other.num_element)
	{
	}

	hashtable &operator(const hashtable& other)
	{

	}
	~hashtable()
	{

	}

	size_type size() const { return num_element; }
	size_type max_size() cosnt { return size_type(-1); }
	bool empty() const { return size() == 0; }
	
	void swap(const hashtable& other)
	{
		lsstd::swap(hash, other.hash);
		lsstd::swap(equals, other.equals);
		lsstd::swap(get_key, other.get_key);
		lsstd::swap(num_element, other.num_element);
		buckets.swap(other.buckets);
	}

	iterator begin()
	{
		for (size_type i = 0; i < buckets.size(); ++i)
		{
			if (buckets[i])
			{
				return iterator(buckets[i], this);
			}
		}
		return end();
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
	const_iterator begin() const
	{
		for (size_type i = 0; i < buckets.size(); ++i)
		{
			if (buckets[i])
			{
				return const_iterator(buckets[i], this);
			}
		}
		return end();
	}
	const_iterator end() const
	{
		return const_iterator(nullptr, this);
	}

};
__STL_END_NAMESPACE