#pragma once
#include "stl_config.h"
#include "stl_alloc.h"
#include <xutility>
#include "stl_pair.h"
#include "stl_algo.h"


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




template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc=allocator<hashtable_node<Value>>>
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

protected:
	using _Node = hashtable_node<Value>;
public:
	using allocator_type = typename allocator<_Node>;
	allocator_type get_allocator() const {
		return node_allocator;
	}
private:
	allocator_type node_allocator;
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
		_M_initialize_buckets(size);
	}

	hashtable(size_type size,
		const HashFun& in_hf,
		const EqualKey& in_equal_key,
		const allocator_type& a = allocator_type())
		: node_allocator(a), hash(in_hf), equals(in_equal_key), get_key(ExtractKey()), buckets(a), num_element(0)
	{
		_M_initialize_buckets(size);
	}

	hashtable(const hashtable& other)
		: node_allocator(other.get_allocator()), 
		hash(other.hash), 
		equals(other.equals), 
		get_key(other.get_key),
		buckets(other.get_allocator()), 
		num_element(other.num_element)
	{
		_M_copy_from(other);
	}

	hashtable &operator=(const hashtable& other)
	{
		if (&other != this)
		{
			clear();
			hash = other.hash;
			equals = other.equals;
			get_key = other.get_key;
			_M_copy_from(other);
		}
		return *this;
	}
	~hashtable()
	{
		clear();
	}

	size_type size() const { return num_element; }
	size_type max_size() const { return size_type(-1); }
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

public:
	size_type bucket_count() const { return buckets.size(); }

	size_type max_bucket_count() const { return __stl_prime_list[__stl_num_primes - 1]; }

	//获取bucket的链表元素数量
	size_type elements_in_bucket(size_type bucket_index)
	{
		size_type n = 0;
		for (_Node * cur = buckets[bucket_index]; cur != nullptr; cur = cur->next)
		{
			++n;
		}
		return n;
	}

	pair<iterator, bool> insert_unique(const value_type& obj)
	{
		resize(num_element + 1);
		return insert_unique_noresize(obj);
	}

	iterator insert_equal(const value_type& obj)
	{
		resize(num_element + 1);
		return insert_unique_noresize(obj);
	}

	pair<iterator, bool> insert_unique_noresize(const value_type& obj)
	{
		// 计算bucket 索引
		const size_type n = _M_bkt_num(obj);

		_Node* first = buckets[n];
		for (_Node* cur = first; cur; cur = cur->next)
		{
			if (equals(get_key(cur->val), get_key(obj)))
			{
				// hashtable里面已经存在，则直接返回，不能插入
				return pair<iterator, bool>(iterator(cur, this), false);
			}
		}

		// 没有找到，需要新建一个node
		_Node* tmp_node = _M_new_node(obj);
		tmp_node->next = first;
		buckets[n] = tmp_node;
		++num_element;
		return pair<iterator, bool>(iterator(tmp_node, this), true);
	}
	iterator insert_equal_noresize(const value_type& obj)
	{
		// 计算bucket 索引
		const size_type n = _M_bkt_num(obj);

		_Node* first = buckets[n];
		for (_Node* cur = first; cur; cur = cur->next)
		{
			if (equals(get_key(obj), get_key(cur->val)))
			{
				_Node* tmp_node = _M_new_node(obj);
				tmp_node->next = cur->next;
				cur->next = tmp_node;
				++num_element;
				return iterator(tmp_node, this);
			}
		}
		_Node* tmp_node = _M_new_node(obj);
		tmp_node->next = first;
		buckets[n] = tmp_node;
		++num_element;
		return iterator(tmp_node, this);
	}

	reference find_or_insert(const value_type& obj)
	{
		resize(num_element + 1);

		size_type n = _M_bkt_num(obj);
		_Node* first = buckets[n];
		for (_Node* cur = first; cur; cur = cur->next)
		{
			if (equals(get_key(obj), get_key(cur->val)))
			{
				return cur->val;  // 找到直接返回
			}
		 }
		_Node* tmp = _M_new_node(obj);
		tmp->next = buckets[n];
		buckets[n] = tmp;
		++num_element;
		return tmp->val;
	}

	iterator find(const key_type& key)
	{
		size_type n = _M_bkt_num_key(key);
		_Node* first = nullptr;
		for(first = buckets[n]; first && (!equals(get_key(first->val), key)); first = first->next)
		{ }
		return iterator(first, this);
	}

	size_type count(const key_type& key) const
	{
		const size_type n = _M_bkt_num_key(key);
		size_type result = 0;
		for (const _Node* cur = buckets[n]; cur; cur = cur->next)
		{
			if (equals(key, get_key(cur->val)))
			{
				++result;
			}
		}
		return result;
	}

	
	pair<iterator, iterator> equal_range(const key_type& key)
	{
		return pair<iterator, iterator>();
	}
	pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return pair<const_iterator, const_iterator>();
	}

	size_type erase(const key_type& key)
	{
		const size_type n = _M_bkt_num_key(key); 
		_Node* first = buckets[n];

		size_type erase_count = 0;
		if (first != nullptr)
		{
			_Node* cur = first;
			_Node* next = cur->next;
			while (next)
			{
				if (equals(get_key(next->val), key))
				{
					cur->next = next->next;
					_M_delete_node(next);
					next = cur->next;
					--num_element;
					++erase_count;
				}
				else
				{
					cur = next;
					next = cur->next;
				}
			}
		}
		if (equals(get_key(first), key))
		{
			buckets[n] = first->next;
			_M_delete_node(first);
			++erase_count;
			--num_element;
		}
		return erase_count;
	}
	void erase(const iterator& iter)
	{
		_Node* node = iter.cur_node;
		if (node)
		{
			const size_type n = _M_bkt_num(node->val);
			_Node* cur = buckets[n];
			if (cur == node)
			{
				buckets[n] = cur->next;
				_M_delete_node(cur);
				--num_element;
			}
			else
			{
				_Node* next = cur->next;
				while (next)
				{
					if (next == node)
					{
						cur->next = next->next;
						_M_delete_node(next);
						--num_element;
						break;
					}
					else
					{
						cur = next;
						next = cur->next;
					}
				}
			}
		}
	}
	void erase(iterator first, iterator last)
	{
		size_type first_bucket = first.cur_node ? _M_bkt_num(first.cur_node->val) : buckets.size();
		size_type last_bucket = last.cur_node ? _M_bkt_num(last.cur_node->val) : buckets.size();
		if (first.cur_node == last.cur_node)
		{
			return;
		}
		else if (first_bucket == last_bucket)
		{
			_M_erase_bucket(first_bucket, first.cur_node, last.cur_node);
		}
		else
		{
			_M_erase_bucket(first_bucket, first.cur_node, nullptr);
			for (size_type n = first_bucket + 1; n < last_bucket; ++n)
			{
				_M_erase_bucket(n, nullptr);
			}
			if (last_bucket != buckets.size())
			{
				_M_erase_bucket(last_bucket, last.cur_node);
			}
		}
	}

	void erase(const const_iterator& iter)
	{
		//erase(iterator(const_cast<_Node*>(iter.cur_node), const_cast<hashtable*>(iter.ht));
	}
	void erase(const_iterator first, const_iterator last)
	{
		erase(iterator(const_cast<_Node*>(first.cur_node),
			const_cast<hashtable*>(first.ht)),
			iterator(const_cast<_Node*>(last.cur_node),
				const_cast<hashtable*>(last.ht)));
	}

	void resize(size_type num_element_hint);
	void clear();

private:
	size_type _M_next_size(size_type n) const
	{
		return __stl_next_prime(n);
	}

	void _M_initialize_buckets(size_type n)
	{
		const size_type n_buckets = _M_next_size(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, nullptr);
		num_element = 0;
	}

	// 计算key的哈希值
	size_type _M_bkt_num_key(const key_type& key) const
	{
		return _M_bkt_num_key(key, buckets.size());
	}

	// 计算value对应key的哈希值
	size_type _M_bkt_num(const value_type& obj) const
	{
		return _M_bkt_num_key(get_key(obj), buckets.size());
	}

	// 计算key的哈希值
	size_type _M_bkt_num_key(const key_type& key, size_type n) const
	{
		return hash(key) % n;
	}

	size_type _M_bkt_num(const value_type& obj, size_type n) const
	{
		return _M_bkt_num_key(get_key(obj), n);
	}

	_Node* _M_new_node(const value_type& obj, size_type n) const
	{
		_Node* node = get_node();
		node->next = nullptr;
		construct(&node->val, obj);
		return node;
	}

	void _M_delete_node(_Node* node)
	{
		destroy(&node->val);
		put_node(node);
	}

	void _M_erase_bucket(const size_type n, _Node* first, _Node* last)
	{
		_Node* cur = buckets[n];
		if (cur == first)
		{
			_M_erase_bucket(n, last);
		}
		else
		{
			_Node* next = nullptr;
			for (next = cur->next; next != first; cur = next, next = cur->next)
			while (next != last)
			{
				cur->next = next->next;
				_M_delete_node(next);
				next = cur->next;
				--num_element;
			}
		}
	}
	void _M_erase_bucket(const size_type n, _Node* last)
	{
		_Node* cur = buckets[n];
		while (cur != last)
		{
			_Node* next = cur->next;
			_M_delete_node(cur);
			cur = next;
			buckets[n] = cur;
			--num_element;
		}
	}

	void _M_copy_from(const hashtable& other)
	{
		buckets.clear();
		buckets.reserve(other.buckets.size());
		buckets.insert(buckets.end(), other.buckets.size(), nullptr);
		for (size_type n = 0; n < other.buckets.size(); ++n)
		{
			const _Node* cur = other.buckets[n];
			if (cur)
			{
				_Node* copy_node = _M_new_node(cur->val);
				buckets[n] = copy_node;
				for (_Node* next = cur->next; next; cur = next, next = next->next)
				{
					copy_node->next = _M_new_node(next->val);
					copy_node = copy_node->next;
				}
			}
		}
		num_element = other.num_element;
	}
};



//////////////////////////////////////////////////////////////////////////
// iterator
template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
hashtable_iterator< Value, Key, HashFun, ExtractKey, EqualKey, Alloc>& 
hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++()
{
	const _Node* old = cur_node;
	cur_node = cur_node->next;
	if (cur_node == nullptr)
	{
		// 需要获得下一个链表的头结点
		size_type bucket_hash = ht->_M_bkt_num(old->val);
		while (cur_node == nullptr && ++bucket_hash < ht->buckets.size())
		{
			cur_node = ht->buckets[bucket_hash];
		}
	}
	return *this;
}


template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
hashtable_iterator< Value, Key, HashFun, ExtractKey, EqualKey, Alloc>
hashtable_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++(int)
{
	iterator tmp = *this;
	++*this;
	return tmp;
}


//////////////////////////////////////////////////////////////////////////
// const_iterator
template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
hashtable_conster_iterator< Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&
hashtable_conster_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++()
{
	const _Node* old = cur_node;
	cur_node = cur_node->next;
	if (cur_node == nullptr)
	{
		// 需要获得下一个链表的头结点
		size_type bucket_hash = ht->_M_bkt_num(old->val);
		while (cur_node == nullptr && ++bucket_hash < ht->buckets.size())
		{
			cur_node = ht->buckets[bucket_hash];
		}
	}
	return *this;
}


template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
hashtable_conster_iterator< Value, Key, HashFun, ExtractKey, EqualKey, Alloc>
hashtable_conster_iterator<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::operator++(int)
{
	hashtable_conster_iterator tmp = *this;
	++*this;
	return tmp;
}

//////////////////////////////////////////////////////////////////////////
// hashtable operator ==
template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
bool operator==(
	const hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&ht1,
	const hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>& ht2)
{
	using _Node = typename hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::_Node;
	if (ht1.buckets.size() != ht2.buckets.size())
	{
		return false;
	}
	for (int n = 0; n < ht1.buckets.size(); ++n)
	{
		_Node* cur1 = ht1.buckets[n];
		_Node* cur2 = ht2.buckets[n];
		for (; cur1 && cur2 && cur1->val == cur2->val; cur1 = cur1->next, cur2 = cur2->next)
		{
		}
		if (cur1 || cur2)
		{
			return false;
		}
	}
	return true;
}

template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
bool operator!=(
	const hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&ht1,
	const hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>& ht2)
{
	return !(ht1 == ht2);
}

template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
inline void swap(hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>&ht1,
	hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>& ht2)
{
	ht1.swap(ht2);
}

//////////////////////////////////////////////////////////////////////////
// hashtable

template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::resize(size_type num_element_hint)
{
	const size_type old_n = buckets.size();

	if (num_element_hint > old_n)
	{
		const size_type new_size = _M_next_size(num_element_hint);
		if (new_size > old_n)
		{
			vector<_Node*, Alloc> tmp_buckets(new_size, nullptr, buckets.get_allocator());
			for (size_type bucket = 0; bucket < old_n; ++bucket)
			{
				_Node* first = buckets[bucket];
				while (first != nullptr)
				{
					// 计算新的散列值
					size_type new_bucket = _M_bkt_num(first->val, new_size);
					buckets[bucket] = first->next;
					first->next = tmp_buckets[new_bucket];
					tmp_buckets[new_bucket] = first;
					first = buckets[bucket];
				}
			}
			buckets.swap(tmp_buckets);
		}
	}
}

template<class Value, class Key, class HashFun, class ExtractKey, class EqualKey, class Alloc>
void hashtable<Value, Key, HashFun, ExtractKey, EqualKey, Alloc>::clear()
{
	for (size_type n = 0; n < buckets.size(); ++n)
	{
		_Node* first = buckets[n];
		while (first != nullptr)
		{
			_Node* next = first->next;
			_M_delete_node(first);
			first = next;
		}
		buckets[n] = nullptr;
	}
	num_element = 0;
}
__STL_END_NAMESPACE