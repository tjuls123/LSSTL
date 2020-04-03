
#include "type_traits.h"
#include <iostream>
#include "stl_alloc.h"
#include <vector>
using namespace std;

int main()
{
	cout << lsstd::bool_constant<true>::value << endl;


	cout << sizeof(const int) << endl; // 4
	cout << sizeof(const int*) << endl; // 8
	cout << sizeof(int[23]) << endl;  // 92
	cout << sizeof(const volatile int) << endl;  // 4
	int *p = nullptr;
	cout << sizeof(p) << endl;
	cout << sizeof(lsstd::bool_constant<true>::type) << endl;
	system("pause");
}