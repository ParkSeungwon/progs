#include<iostream>
using namespace std;

struct A {
	int a, b, c;
};

int main()
{
	A a{ .a=1, .b=4, .c=2 };

	cout << a.a << ' ' << a.b << ' ' << a.c << endl;

	int k[] = {
		[0] = 1, [1] = 2, [2]=1
	};
}

