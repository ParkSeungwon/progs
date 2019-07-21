#include<regex>
#include<string>
#include<iostream>
using namespace std;

int main(int ac, char** av) 
{// echo "'http://www.naver.com'" | reg.x b com
	string s, s2;
	regex e{string(R"([\'\"]http://\S+)") + av[2] + R"([\'\"])"};
	smatch m;
	char c;
	while(cin >> noskipws >> c) s += c;
	while(regex_search(s, m, e)) {
		for(auto& a : m) s2 += a;
		s2.erase(0,1);//remove ' or "
		s2.pop_back();
		if(*av[1] == 'd') {
			s2.insert(0, "wget -t 0 ");
			system(s2.data());
		} else if(*av[1] == 'b') {
			if(s2.back() == '/') s2.pop_back();
			s2.erase(0, 7);
			s2.insert(0, "tel.x `addr ");
			s2.append("` 80 GET / HTTP/1.0\n\n");
			system(s2.data());
		} else cout << s2 << endl;
		s = m.suffix().str();
		s2.clear();
	}
}

