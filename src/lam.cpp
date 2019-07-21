#include<string>
#include<vector>
#include<functional>
#include<iostream>
using namespace std;
using namespace std::placeholders;

template<class T> struct S {
	string f(string s) {
		return s + 'm';
	}
};

struct S2 : S<int> {
	template<string(S<int>::*FP)(string)>
	vector<unsigned char> trans(vector<unsigned char> s) {
		vector<unsigned char> v; string t;
		for(unsigned char c : s) t += c;
		for(unsigned char c : (this->*FP)(t)) v.push_back(c);
		return v;
	}
};

template<int(*P)(int)> int f() {
	return (*P)(3);//pointer template
}
int g(int k) { return k; }

int main()
{
	S<int> s;
	S2 s2;
	auto r = s2.trans<&S<int>::f>(vector<unsigned char>{'c', 'd', 'e'});
	for(unsigned char c : r) cout << c;

	cout << f<&g>();
}

