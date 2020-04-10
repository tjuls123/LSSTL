
#include "type_traits.h"
#include <iostream>
#include "stl_alloc.h"
#include <vector>
#include"stl_vector.h"
#include <algorithm>
#include "stl_list.h"
#include"stl_heap.h"
#include "stl_initializer_list.h"
#include "stl_hashtable.h"
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


class A
{
public:
	virtual void func() {
		cout << "A:func" << endl;
	}

	void ff(int a) {
		cout << "ff" << endl;
	}

	void ff(int a) const  {
		cout << "const ff" << endl;
	}

};

class B : public A
{
private:
	virtual void func()
	{
		cout << "B:func" << endl;
	}
};
int main()
{
	system("pause");
}