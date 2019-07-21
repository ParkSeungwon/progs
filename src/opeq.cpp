#include<iostream>
using namespace std;

class A 
{
public:
	int i;
	A& operator=(int k) {
		i = k;
	}
};

class B : public A
{
public:
	B(int a) {
		A::operator=(a);
		cout << i;
	}
};


int main()
{
	A a;
	B b(3);
}
