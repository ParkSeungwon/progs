#include<iostream>
#include<fstream>
using namespace std;

int main()
{
	ifstream f("/dev/memory");
	char c;
	while(f >> c) cout << c; 
}
