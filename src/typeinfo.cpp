#include<iostream>
#include<typeinfo>
#include<vector>
#include<cassert>
using namespace std;

template <class T> class A {
	T a;
};

template <class T> void f(T n)
{
	if(typeid(n) != typeid(A<int>)) cout << "invalid" << endl;
}

int main()
{
	vector<int> v, v2;
	vector<float> v3;
	A<int> a,b;
	cout << typeid(b).name() << endl;
	cout << typeid(a).name() << endl;
	assert(typeid(v) == typeid(v2));
	f(a);
}
