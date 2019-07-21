#include<iostream>
#include<string>
using namespace std;

int main()
{
	char buf[20] = "fjdskljk";
	string s{buf, 0};
	//string s2{buf, -1};
	string s3{buf, 4};
	cout << s << endl  << endl << s3 << endl;
}

