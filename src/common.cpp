#include<iostream>       // std::cout
#include<sstream>
#include<string>
#include<map>
#include<regex>
#include<vector>
#include<utility>
using namespace std;
void GetUnicodeChar(unsigned int code, char chars[5]) {
    if (code <= 0x7F) {
        chars[0] = (code & 0x7F); chars[1] = '\0';
    } else if (code <= 0x7FF) {
        // one continuation byte
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xC0 | (code & 0x1F); chars[2] = '\0';
    } else if (code <= 0xFFFF) {
        // two continuation bytes
        chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xE0 | (code & 0xF); chars[3] = '\0';
    } else if (code <= 0x10FFFF) {
        // three continuation bytes
        chars[3] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xF0 | (code & 0x7); chars[4] = '\0';
    } else {
        // unicode replacement character
        chars[2] = 0xEF; chars[1] = 0xBF; chars[0] = 0xBD;
        chars[3] = '\0';
    }
}
/*
int main()
{
	string s;
	while(getline(cin, s)) {
		stringstream ss;
		ss << s;
		ss >> s; cout << s << ' ';
		ss >> s; cout << s << ' ';
		int n;
		for(int i=0; i<3; i++) {
			ss >> hex >> n;
			char c[5];
			GetUnicodeChar(n, c);
			cout << c;
		}
		cout << ' ';
		ss >> s; cout << s << ' ';
		ss >> s; cout << s << ' ' << endl;
	}
}
*/
int main()
{
	int n;
	string s1, s2;
	map<string, pair<int,string>> m;
	regex r{R"(\S+@\S+\.\S+)"};
	while(cin >> s1) {
		if(regex_match(s1, r)) {
			m[s1].first++;
			m[s1].second = s2;
		}
		s2 = s1;
	}
	vector<pair<pair<int,string>, string>> v;
	for(auto& a : m) v.push_back({a.second, a.first});
	sort(v.begin(), v.end());
	for(auto& a : v) cout << a.first.first << ' ' << a.first.second << ' ' << a.second << endl;
}

