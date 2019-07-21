#include<regex>
#include<iostream>
#include<string>
using namespace std;

int main()
{
	string s;
	regex e{R"((,\d)([^,\d]))"};
	while(getline(cin, s)) cout << regex_replace(s, e, "$1,$2") << endl;
}
