#pragma once

#include "stl_config.h"


__STL_BEGIN_NAMESPACE

template<class T>
class __avl_tree_node
{
public:
	T value_filed;
	size_t height;
	__avl_tree_node* left;
	__avl_tree_node* right;

	__avl_tree_node(T value, __avl_tree_node* in_left, __avl_tree_node* r)
		: value_filed(value), left(in_left), right(r)
	{}
};

template<class T>
class avl_tree
{
public:
	using size_type = size_t;

protected:
	using avl_tree_node = __avl_tree_node<T>;
protected:
	avl_tree_node* m_root;

public:
	avl_tree()
		:m_root(nullptr)
	{

	}
	~avl_tree()
	{
		destroy(m_root);
	}
	size_type height() const
	{
		return get_height(m_root);
	}
	template<class Func>
	void preOrder(Func func)
	{
		preOrder(m_root, func);
	}
	template<class Func>
	void inOrder(Func func)
	{
		inOrder(m_root, func);
	}
	template<class Func>
	void postOrder(Func func)
	{
		postOrder(m_root, func);
	}

	T minimum() const
	{
		if (m_root == nullptr)
		{
			return T();
		}
		avl_tree_node* p = m_root;
		while (p->left != nullptr)
		{
			p = p->left;
		}
		return p->value_filed;
	}
	T maximum() const
	{
		if (m_root == nullptr)
		{
			return T();
		}
		avl_tree_node* p = m_root;
		while (p->right != nullptr)
		{
			p = p->right;
		}
		return p->value_filed;
	}

	avl_tree_node* find(const T& key)
	{
		return find(m_root, key);
	}
	avl_tree_node* iterative_find(const T& key)
	{
		return iterative_find(m_root, key);
	}
	void insert(T key)
	{
		insert(m_root, key);
	}

	void remove(const T& key)
	{
		avl_tree_node* node = find(m_root, key);
		if (node != nullptr)
		{
			remove(m_root, node);
		}
	}
	void destroy()
	{
		destroy(m_root);
	}
	void print()
	{
	
	}
protected:

	avl_tree_node* minimum(avl_tree_node* tree) const
	{
		if (tree == nullptr)
		{
			return nullptr;
		}
		avl_tree_node* p = tree;
		while (p->left != nullptr)
		{
			p = p->left;
		}
		return p;
	}
	avl_tree_node* maximum(avl_tree_node* tree) const
	{
		if (tree == nullptr)
		{
			return nullptr;
		}
		avl_tree_node* p = tree;
		while (p->right != nullptr)
		{
			p = p->right;
		}
		return p;
	}

	size_type get_height(avl_tree_node* tree) const
	{
		if (tree == nullptr)
		{
			return 0;
		}
		size_type left_height = get_height(tree->left);
		size_type right_height = get_height(tree->right);
		return left_height > right_height ? left_height + 1 : right_height;
	}
	template<class Func>
	void preOrder(avl_tree_node* tree, Func func) const
	{
		if (tree == nullptr)
			return;
		func(tree->value_filed);
		preOrder(tree->left, func);
		preOrder(tree->right, func);
	}
	template<class Func>
	void inOrder(avl_tree_node* tree, Func func) const
	{
		if (tree == nullptr)
			return;
		inOrder(tree->left, func);
		func(tree->value_filed);
		inOrder(tree->right, func);
	}
	template<class Func>
	void postOrder(avl_tree_node* tree, Func func) const
	{
		if (tree == nullptr)
			return;
		func(tree->value_filed);
		postOrder(tree->left, func);
		postOrder(tree->right, func);
		func(tree->value_filed);
	}

	avl_tree_node* insert(avl_tree_node* &tree, const T& key)
	{
		if (tree == nullptr)
		{
			tree = get_node(key);
		}
		else if (key < tree->value_filed)
		{
			tree->left = insert(tree->left, key);
			if (get_height(tree->left) - get_height(tree->right) > 1)
			{
				if (key < tree->left->value_filed)
				{
					tree = LLRotation(tree);
				}
				else
				{
					LLRotation(tree);
				}
			}
		}
		else if(key > tree->value_filed)
		{
			tree->right = insert(tree->right, key);
			if (get_height(tree->right) - get_height(tree->left) > 1)
			{
				if (key > tree->right->value_filed)
				{
					tree = RRRotation(tree);
				}
				else
				{
					tree = RLRotation(tree);
				}
			}
		}
		else
		{
			
		}
		tree->height = max(get_height(tree->left), get_height(tree->right)) + 1;
		return tree;
	}
	avl_tree_node* remove(avl_tree_node* &tree, avl_tree_node* node)
	{
		if (tree == nullptr || node == nullptr)
		{
			return nullptr;
		}
		if (node->value_filed < tree->value_filed)
		{
			// 删除节点在左子树
			tree->left = remove(tree->left, node);
			if (get_height(tree->right) - get_height(tree->left) > 1)
			{
				avl_tree_node* right_node = tree->right;
				if (get_height(right_node->left) > get_height(right_node->right))
				{
					tree = RLRotation(tree);
				}
				else
				{
					tree = RRRotation(tree);
				}
			}
		}
		else if (node->value_filed > tree->value_filed)
		{
			tree->right = remove(tree->right, node);
			if (get_height(tree->left) - get_height(tree->right) > 1)
			{
				avl_tree_node* left_node = tree->left;
				if (get_height(left_node->left) > get_height(left_node->right))
				{
					tree = LLRotation(tree);
				}
				else
				{
					tree = LRRotation(tree);
				}
			}
		}
		else
		{
			// 对应要删除的点
			if ((tree->left != nullptr) && (tree->right != nullptr))
			{
				if (get_height(tree->left) > get_height(tree->right))
				{
					avl_tree_node* max_node = maximum(tree->left);
					tree->value_filed = max_node->value_filed;
					tree->left = remove(tree->left, max_node);
				}
				else
				{
					avl_tree_node* min_node = minimum(tree->right);
					tree->value_filed = min_node->value_filed;
					tree->right = remove(tree->right, min_node);
				}
			}
			else
			{
				avl_tree_node* tmp = tree;
				tree = tree->left != nullptr ? tree->left : tree->right;
				destroy_node(tmp);
			}
		}
		return tree;
	}
	avl_tree_node* find(avl_tree_node* tree, const T& key) const
	{
		if (tree == nullptr || tree->value_filed == key)
		{
			return tree;
		}
		if (key < tree->value_filed)
		{
			return find(tree->left, key);
		}
		else
		{
			return find(tree->right, key);
		}
	}
	avl_tree_node* iterative_find(avl_tree_node* tree, const T& key) const
	{
		while (tree != nullptr && tree->value_filed != key)
		{
			if (key < tree->value_filed)
			{
				tree = tree->left;
			}
			else
			{
				tree = tree->right;
			}
		}
		return tree;
	}
	void destroy(avl_tree_node* tree)
	{
		if (tree == nullptr)
		{
			return;
		}
		destroy(tree->left);
		destroy(tree->right);
		destroy_node(tree);
	}

	avl_tree_node* get_node(const T& key)
	{
		return new avl_tree_node(key, nullptr, nullptr);
	}
	void destroy_node(avl_tree_node* node)
	{
		delete node;
	}

	avl_tree_node* LLRotation(avl_tree_node* adjust_root)
	{
		avl_tree_node* adjust_root_left = adjust_root->left;
		adjust_root->left = adjust_root_left->right;
		adjust_root_left->right = adjust_root;

		adjust_root->height = max(get_height(adjust_root->left), get_height(adjust_root->right)) + 1;
		adjust_root_left->height = max(get_height(adjust_root_left->left), get_height(adjust_root_left->right)) + 1;
		return adjust_root_left;
	}

	avl_tree_node* RRRotation(avl_tree_node* adjust_root)
	{
		avl_tree_node* adjust_root_right = adjust_root->right;
		adjust_root->right = adjust_root_right->left;
		adjust_root_right->left = adjust_root;

		adjust_root->height = max(get_height(adjust_root->left), get_height(adjust_root->right)) + 1;
		adjust_root_right->height = max(get_height(adjust_root_right->left), get_height(adjust_root_right->right)) + 1;
		return adjust_root_right;
	}

	avl_tree_node* LRRotation(avl_tree_node* adjust_root)
	{
		adjust_root->left = RRRotation(adjust_root->left);
		return LLRotation(adjust_root);
	}

	avl_tree_node* RLRotation(avl_tree_node* adjust_root)
	{
		adjust_root->right = LLRotation(adjust_root->right);
		return RRRotation(adjust_root);
	}
};
__STL_END_NAMESPACE