
#include "type_traits.h"
#include <iostream>
#include "stl_alloc.h"
#include <vector>
#include"stl_vector.h"
#include <algorithm>
#include "stl_list.h"
#include"stl_heap.h"
#include "stl_alloc.h"
#include "stl_initializer_list.h"
#include "stl_hashtable.h"
#include "stl_function.h"
#include"stl_pair.h"
#include"stl_rb_tree.h"
#include "stl_avl_tree.h"
#include "stl_graph.h"
using namespace std;


template<class InputIterator>
void print_container(InputIterator first, InputIterator last)
{
	for (; first != last; ++first)
	{
		cout << *first << ' ';
	}
	cout << endl;
}

struct Print
{
	void operator()(rsize_t n, lsstd::vector<int>& val)
	{
		cout << n << ": ";
		for(size_t n = 0; n < val.size(); ++n)
			cout << val[n] << " ";
		cout << endl;
	}
};

struct AVLOrder
{
	void operator()(const int& val)
	{
		cout << val << endl;
	}
};

int main()
{
// 	lsstd::hashtable<int, int, lsstd::hash<int>, lsstd::identity<int>, lsstd::equal_to<int>> ht(50, lsstd::hash<int>(), lsstd::equal_to<int>());
// 	cout << ht.size() << endl;
// 	cout << ht.bucket_count() << endl;
// 	cout << ht.max_bucket_count() << endl;
// 
// 	
// 	ht.insert_equal_noresize(4);
// 	ht.insert_equal_noresize(4);
// 	ht.insert_equal_noresize(454);
// 	ht.insert_unique_noresize(554);
// 	ht.insert_unique_noresize(454);
// 	ht.insert_unique_noresize(46);
// 	ht.insert_unique_noresize(44);
// 	ht.insert_equal_noresize(24);
// 	ht.insert_equal_noresize(47);
// 	ht.insert_equal_noresize(445);
// 	ht.insert_equal_noresize(4);
// 	ht.insert_equal_noresize(4);
// 	ht.insert_equal_noresize(454);
// 	ht.insert_equal_noresize(554);
// 	ht.insert_equal_noresize(454);
// 	ht.insert_equal_noresize(46);
// 	ht.insert_equal_noresize(44);
// 	ht.insert_equal_noresize(24);
// 	ht.insert_equal_noresize(47);
// 	ht.insert_equal_noresize(445);
// 	ht.insert_equal_noresize(49);
// 	ht.print(Print());
// 	pair<int, bool>(2, false);

	lsstd::avl_tree<int> avl;
	avl.insert(34);
	avl.insert(5);
	avl.insert(344);
	avl.insert(55);
	avl.inOrder(AVLOrder());
	using d = lsstd::rb_tree<int, int, lsstd::identity<int>, lsstd::equal_to<int>>;
	
	mst_prim(get_graph_matrix(), 0);
	cout << "kruskal" << endl;
	mst_kruskal(get_graph_matrix());
	system("pause");
}