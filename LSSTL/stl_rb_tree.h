#pragma once
#include "stl_config.h"
#include "stl_iterator_base.h"
#include <vcruntime_exception.h>
#include "stl_pair.h"

__STL_BEGIN_NAMESPACE

using __rb_tree_color_type = bool;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base
{
	using color_type = __rb_tree_color_type;
	using base_ptr = __rb_tree_node_base * ;

	color_type color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	static base_ptr minimun(base_ptr x)
	{
		while (x->left != nullptr) x = x->left;
		return x;
	}
	static base_ptr maximun(base_ptr x)
	{
		while (x->right != nullptr) x = x->right;
		return x;
	}
};

template<class Value>
struct __rb_tree_node : public __rb_tree_node_base
{
	using link_type = __rb_tree_node<Value>;
	Value value_field;
};


struct __rb_tree_base_iterator
{
	using base_ptr = __rb_tree_node_base::base_ptr;
	using iterator_category = bidirectional_iterator_tag;
	using difference_type = ptrdiff_t;
	base_ptr node;

	void increment()
	{
		if (node->right != nullptr)
		{
			node = node->right;
			while (node->left != nullptr)
			{
				node = node->left;
			}
		}
		else
		{
			base_ptr y = node->parent;
			while (y->right == node)
			{
				node = y;
				y = y->parent;
			}
			if (node->right != y)
			{
				node = y;
			}
		}
	}
	void decrement()
	{
		if (node->color == __rb_tree_red && node->parent->parent == node)
		{
			node = node->right;
		}
		else if (node->left != nullptr)
		{
			base_ptr y = node->left;
			while (y->right != nullptr)
			{
				y = y->right;
			}
			node = y;
		}
		else
		{
			base_ptr  y = node->parent;
			while (node == y->left)
			{
				node = y;
				y = y->parent;
			}
			node = y;
		}
	}
};


template<class Value, class Ref, class Ptr>
struct __rb_tree_iterator :public __rb_tree_base_iterator
{
	using value_type = Value;
	using reference = Ref;
	using pointer = Ptr;
	using iterator = __rb_tree_iterator<Value, Value&, Value*>;
	using const_iterator = __rb_tree_iterator<Value, const Value&, const Value*>;
	using link_type = __rb_tree_node<Value>*;

	using self = __rb_tree_iterator<Value, Ref, Ptr>;

	__rb_tree_iterator() {}
	__rb_tree_iterator(link_type x) : node(x){}
	__rb_tree_iterator(const iterator &it) : node(it.node) {}
	reference operator*() const { return link_type(node)->value_field; }

	self& operator++()
	{
		increment();
		return *this;
	}
	self operator++(int)
	{
		self tmp = *this;
		increment();
		return tmp;
	}
	self &operator--()
	{
		decrement();
		return *this;
	}
	self operator--(int)
	{
		self tmp = *this;
		decrement();
		return tmp;
	}

};

inline bool operator==(const __rb_tree_base_iterator& x, const __rb_tree_base_iterator& y)
{
	return x.node == y.node;
}

inline bool operator!=(const __rb_tree_base_iterator& x, const __rb_tree_base_iterator& y)
{
	return x.node != y.node;
}


inline bidirectional_iterator_tag
iterator_cagegory(const __rb_tree_base_iterator& iter)
{
	return bidirectional_iterator_tag();
}

inline __rb_tree_base_iterator::difference_type*
distance_type(const __rb_tree_base_iterator& iter)
{
	return static_cast<__rb_tree_base_iterator::difference_type*>(0);
}

template<class Value, class Ref, class Ptr>
inline Value* value_type(const __rb_tree_iterator<Value, Ref, Ptr>&)
{
	return static_cast<Value*>(0);
}



template<class Key, class Value, class KeyOfValue, class Compare, class Alloc=allocator<Key>>
class rb_tree
{
protected:
	using void_pointer = void*;
	using base_ptr = __rb_tree_node_base * ;
	using rb_tree_node = __rb_tree_node<Value>;
	using rb_tree_node_allocator = allocator<rb_tree_node>;
	using color_type = __rb_tree_color_type;

public:
	using key_type = Key;
	using value_type = Value;
	using pointer = value_type * ;
	using const_pointer = const value_type*;
	using reference = value_type & ;
	using const_reference = const value_type&;

	using link_type = rb_tree_node* ;
	using size_type = size_t;
	using difference_type = ptrdiff_t;

	using self = rb_tree<Key, Value, KeyOfValue, Compare, Alloc>;
protected:
	rb_tree_node_allocator node_allocator;
	link_type get_node() { node_allocator.allocate(1); }
	void put_node(link_type p) { node_allocator.deallocate(p); }
	link_type create_node(const value_type& x)
	{
		link_type tmp = get_node();
		construct(&tmp->value_field, x);
		put_node(tmp);

		return tmp;
	}


	link_type clone_node(link_type x)
	{
		link_type tmp = create_node(x);
		tmp->color = x->color;
		tmp->left = nullptr;
		tmp->right = nullptr;
		return tmp;
	}
	void destroy_node(link_type p)
	{
		destroy(&p->value_field);
		put_node(p);
	}

protected:
	size_type node_count;
	link_type header;
	Compare key_compare;

	link_type& root() const { return static_cast<link_type&>(header->parent); }
	link_type& leftmost() const { return static_cast<link_type&>(header->left); }
	link_type& rightmost() const { return static_cast<link_type&>(header->right); }


	static link_type& left(link_type x) { return (link_type&)(x->left); }
	static link_type& right(link_type x) { return (link_type&)(x->right); }
	static link_type& parent(link_type x) { return (link_type&)(x->parent); }
	static reference value(link_type x) { return x->value_field; }
	static const Key& key(link_type x) { return KeyOfValue()(value(x)); }
	static color_type& color(link_type x) { return (color_type&)(x->color); }

	static link_type& left(base_ptr x) { return (link_type&)(x->left); }
	static link_type& right(base_ptr x) { return (link_type&)(x->right); }
	static link_type& parent(base_ptr x) { return (link_type&)(x->parent); }
	static reference value(base_ptr x) { return ((link_type)x)->value_field; }
	static const Key& key(base_ptr x) { return KeyOfValue()(value(link_type(x))); }
	static color_type& color(base_ptr x) { return (color_type&)(link_type(x)->color); }

	static link_type minimum(link_type x)
	{
		return static_cast<link_type>(__rb_tree_node_base::minimun(x));
	}
	static link_type maximum(link_type x)
	{
		return static_cast<link_type>(__rb_tree_node_base::maximun(x));
	}

public:
	using iterator = __rb_tree_iterator<value_type, reference, pointer>;
	using const_iterator = __rb_tree_iterator<value_type, const_reference, const_pointer>;

private:
	iterator __insert(base_ptr _x, base_ptr _y, const value_type&v)
	{
		link_type x = static_cast<link_type>(_x);
		link_type y = static_cast<link_type>(_y);
		link_type z;

		// 如果当前rb_tree为空，则y==header条件才成立
		// 如果key_compare(KeyOfValue()(v), key(y))成立，则插入点x位于y的左子节点
		if (y == header || x != nullptr || key_compare(KeyOfValue()(v), key(y)))
		{
			z = create_node(v);
			left(y) = z;
			if (y == header)
			{
				root() = z;
				rightmost() = z;
			}
			else if (y == leftmost())
			{
				leftmost() = z;
			}
		}
		else // 则插入点x位于y的右子节点
		{
			z = create_node(v);
			right(y) = z;
			if (y == rightmost())
			{
				rightmost() = z;
			}
		}

		// 设置z节点的属性
		parent(z) = y;
		left(z) = nullptr;
		right(z) = nullptr;
		++node_count;
		return iterator(z);
	}

	// 将以x为根节点的rb_tree创建rb_tree，并且将创建的根节点的父节点设置为p
	link_type __copy(link_type x, link_type p)
	{
		link_type top = clone_node(x);  //clone 节点
		top->parent = p;  // 
		if (x->right != nullptr)
		{
			top->right = __copy(right(x), top);
		}
		p = top;
		x = left(x);  // copy left
		while (x != nullptr)
		{
			link_type y = clone_node(x);
			p->left = y;
			y->parent = p;
			if (right(x) != nullptr)
			{
				y->right = __copy(right(x), y);
			}
			p = y;
			x = left(x);
		}
		return top;
	}
	void __erase(link_type x)
	{
		while (x != nullptr)
		{
			__erase(right(x));
			link_type y = left(x);
			destroy_node(x);
			x = y;
		}
	}

	void init()
	{
		header = get_node();
		color(header) = __rb_tree_red; // 根节点为红色
		root() = nullptr;
		leftmost() = header;
		rightmost = header;
	}
public:
	rb_tree(const Compare& comp = Compare())
		: node_count(0), key_compare(comp) {
		init();
	}
	rb_tree(const rb_tree& other)
		: node_count(0), key_compare(other.key_compare)
	{
		header = get_node();
		color(header) = __rb_tree_red;
		if (other.root() == nullptr)
		{
			root() = nullptr;
			leftmost() = header;
			rightmost() = header;
		}
		else
		{
			root() = __copy(other.root(), header);
			leftmost() = minimum(root());
			rightmost() = maximun(root());
		}
		node_count = other.node_count;
	}
	~rb_tree()
	{
		clear();
		put_node(header);
	}

	rb_tree& operator=(const rb_tree& other)
	{
		if (this != &other)
		{
			clear();
			node_count = 0;
			key_compare = other.key_compare;
			if (other.root() == nullptr)
			{
				root() == nullptr;
				leftmost() = header;
				rightmost() = header;
			}
			else
			{
				root() = __copy(other.root(), header);
				leftmost() = minimum(root());
				rightmost() = maximum(root());
				node_count = other.node_count;
			}
		}
		return *this;
	}

public:
	Compare key_comp() const { return key_compare; }
	iterator begin() { return leftmost(); }
	const_iterator begin() const { return leftmost(); }
	iterator end() { return header; } // header 隐士转换为iterator
	const_iterator end() const { return header; }

	bool empty() const{ return node_count == 0; }
	size_type size() const { return node_count; }
	size_type max_size() const { return size_type(-1); }

	void swap(rb_tree& other)
	{
		lsstd::swap(header, other.header);
		lsstd::swap(node_count, other.node_count);
		lsstd::swap(key_compare, other.key_compare);
	}

public:
	// 插入值，不允许有重复
	pair<iterator, bool> insert_unique(const value_type& val)
	{
		link_type y = header;
		link_type x = root();
		bool comp = true;
		while (x != nullptr)
		{
			y = x;
			// 如果val的关键字 < key(x)， 往左走
			comp = key_compare(KeyOfValue()(val), key(x)); // key_compare: < 
			x = comp ? left(x) : right(x);
		}
		iterator j = iterator(y);
		if (comp)
		{
			if (j == begin())
			{
				return pair<iterator, bool>(__insert(x, y, val), true);
			}
			else
			{
				--j;
			}
		}
		if (key_compare(key(j), KeyOfValue()(val)))
		{
			return pair<iterator, bool>(__insert(x, y, val), true);
		}
		return pair<iterator, bool>(j, false);
	}
	// 插入值，允许有重复
	iterator insert_equal(const value_type& val)
	{
		link_type y = header;
		link_type x = root();
		while (x != nullptr)
		{
			y = x;
			// 遇大则往左，遇小于等于则往右
			x = key_compare(KeyOfValue()(val), key(x)) ? left(x) : right(x);
		}
		return __insert(x, y, val);
	}
	iterator insert_unique(iterator position, const value_type& x)
	{
		return position;
	}
	iterator insert_equal(iterator position, const value_type& x)
	{
		return position;
	}
	void erase(iterator position)
	{

	}
	// 移除key相等的元素，返回移除的个树数
	size_type erase(const key_type& key)
	{
		pair<iterator, iterator>p = equal_range(key);
		size_type n = distance(p.first, p.second);
		erase(p.first, p.second);
		return n;
	}
	void erase(iterator first, iterator last)
	{
		if (first == begin() && last == end())
		{
			clear();
		}
		else
		{
			while (first != last)
			{
				erase(first++);
			}
		}
	}
	void erase(const key_type* first, const key_type* last)
	{
		while (first != last)
		{
			erase(*first++); // erase(*(first++));
		}
	}
	void clear()
	{
		if (node_count > 0)
		{
			__erase(root());
			leftmost() = header;
			root() = nullptr;
			rightmost() = header;
			node_count = 0;
		}
	}
public:
	iterator find(const key_type& k)
	{
		link_type y = header;
		link_type x = root();
		while (x != nullptr)
		{
			if (!key_compare(key(x), k))
			{
				// 如果x的键值大于k
				y = x;
				x = left(x);
			}
			else
			{
				// 否则x的键值<=k
				x = right(x);
			}
		}
		iterator j = iterator(y);
		return (j == end() || key_compare(k, key(j.node))) ? end() : j;
	}
	const_iterator find(const key_type& k) const {
		link_type y = header;
		link_type x = root();
		while (x != nullptr)
		{
			if (!key_compare(key(x), k))
			{
				// 如果x的键值大于k
				y = x;
				x = left(x);
			}
			else
			{
				// 否则x的键值<=k
				x = right(x);
			}
		}
		const_iterator j = const_iterator(y);
		return (j == end() || key_compare(k, key(j.node))) ? end() : j;
	}
	size_type count(const key_type& key) const
	{
		pair<const_iterator, const_iterator> p = equal_range(key);
		return distance(p.first, p.second);
	}
	iterator lower_bound(const key_type& k)
	{
		link_type y = header;
		link_type x = root();
		while (x != nullptr)
		{
			if (!key_compare(key(x), k))
			{
				// 如果x的键值大于k
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return iterator(y);
	}
	const_iterator lower_bound(const key_type& k) const
	{
		link_type y = header;
		link_type x = root();
		while (x != nullptr)
		{
			if (!key_compare(key(x), k))
			{
				// 如果x的键值大于k
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return const_iterator(y);
	}
	iterator upper_bound(const key_type& k)
	{
		link_type y = header;
		link_type x = root();
		while (x != nullptr)
		{
			if (key_compare(key(x), k))
			{
				// 如果x的键值<=k
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return iterator(y);
	}
	const_iterator upper_bound(const key_type& k) const
	{
		link_type y = header;
		link_type x = root();
		while (x != nullptr)
		{
			if (key_compare(key(x), k))
			{
				// 如果x的键值<=k
				y = x;
				x = left(x);
			}
			else
			{
				x = right(x);
			}
		}
		return const_iterator(y);
	}
	pair<const_iterator, const_iterator> equal_range(const key_type& x) const
	{
		return pair<const_iterator, const_iterator>(lower_bound(x), upper_bound(x));
	}

	pair<iterator, iterator> equal_range(const key_type& x)
	{
		return pair<iterator, iterator>(lower_bound(x), upper_bound(x));
	}
};
__STL_END_NAMESPACE