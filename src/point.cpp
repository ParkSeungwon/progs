#include<iostream>
using namespace std;
int main()
{
	char c[40];
	char *p = c+30;
	cout << p[-3];
}
