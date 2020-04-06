
#include "type_traits.h"
#include <iostream>
#include "stl_alloc.h"
#include <vector>
#include"stl_vector.h"
#include <algorithm>
#include "stl_list.h"
#include"stl_heap.h"
#include "stl_initializer_list.h"
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
	A *pa = new B();
	pa->func();

	int a = reinterpret_cast<int>(pa);
	cout << a << endl;
	system("pause");
}