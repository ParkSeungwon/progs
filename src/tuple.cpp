#include<iostream>
#include<utility>
#include<functional>
using namespace std;

int main()
{
	auto f = [](int a) { return a + 1; };
	tuple<int, function<int(int)>> tp{1, f};
}
