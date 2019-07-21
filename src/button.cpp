#include<iostream>
#include<string>
#include<regex>
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

int main()
{
	string s;
	smatch m;
	stringstream ss;
	int n;
	char re[5];
	regex id{R"foo(userId="(\d{10})")foo"};
	regex mobile{R"foo(phoneMobile="([-\d]{5,15})")foo"};
	regex grade{R"foo(userGrade="([^"]+)")foo"};
	regex name{R"foo(userName="([^"]+)")foo"};
	regex email{R"foo(email="([^"]+@[^"]+)")foo"};
	while(getline(cin, s)) {
		regex_search(s,m,id);
		cout << m[1] << ' ';
		regex_search(s,m,grade);
		ss << m[1];
		ss >> n;
		cout << n;
		char c;
		ss >> c >> c;
		ss >> n;
		GetUnicodeChar(n, re);
		ss >> c >> c;
		ss >> n;
		GetUnicodeChar(n, re);
		cout << re;
		regex_search(s,m,name);
		cout << m[1] << ' ';
		regex_search(s,m,mobile);
		cout << m[1] << ' ';
		regex_search(s,m,email);
		cout << m[1] << ' ';
		cout << endl;
	}
}
	
