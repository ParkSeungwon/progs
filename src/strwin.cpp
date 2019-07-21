#include<iostream>
#include<string>
using namespace std;

struct Interface
{
	static Interface* ip;
	const string s = "haha";
	virtual void show() {}
};

Interface* Interface::ip = nullptr;

struct A : public Interface
{
	A() {
		ip = this;
	}
	int i = 3;
	void show() {
		cout << i << s << endl;
	}
};

struct B : public Interface
{
	B() {
		ip->show();
	}
};

int main()
{
	A a;
	B b;
}

