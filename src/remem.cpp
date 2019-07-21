#include<iostream>
#include<fstream>
#include<random>
#include<string>
#include<cstdlib>
#include<unordered_map>
using namespace std;

class User
{
public:
	User(string pass) : di(48, 122) {
		user = getenv("USER");
		home = getenv("HOME");
		ifstream f(home + "/.pass");
		if(!f.is_open()) {
			password = pass;
			passes[user] = password;
			write();
		} else {
			string s1, s2;
			while(f >> s1 >> s2) passes[decode(s1)] = decode(s2);
			if(passes[user] == pass) {
				password = pass; 
				auto it = passes.begin();
				for(it++; it != passes.end(); it++) 
					cout << it->first << " : " << it->second << endl;
			}
			for(auto it = passes.begin(); it != passes.end(); it++) 
				cout << it->first << " : " << it->second << endl;
		}
	}
	void add(string site, string pass) {
		passes[site] = pass;
		write();
	}
	void write() {
		ofstream f(home + "/.pass");
		for(auto& a : passes) 
			f << encode(a.first) << ' ' << encode(a.second) << endl;
	}

//protected:
	string user;
	string home;
	string password;
	unordered_map<string, string> passes;

//private:
	random_device rd;
	uniform_int_distribution<> di;
	string encode(string s) {
		char rt[300]{};
		for(int i=0, j=0; i<s.size(); i++, j++) {
			for(int k=0; k<password.size(); k++) rt[j++] = di(rd);
			rt[j] = s[i];// + password[i];// + s[i];
		}
		return rt;
	}
	string decode(string s) {
		char rt[20]{};
		password = passes[user];
		for(int i=0, j=0; i<s.size(); i++, j++) {
			for(int k=0; k<password.size(); k++) i++;
			rt[j] = s[i];// - password[i];
		}
		return rt;
	}
};

string get_pass() {
	string s;
	cout << "Enter Password : ";
	system("stty -echo");
	cin >> s;
	system("stty echo");
	return s;
}

int main(int c, char** v)
{
	User u{get_pass()};
	if(v[1] == "add") u.add(v[2], v[3]);
	cout << u.encode("cockcodk0") << endl;
	cout << u.decode(u.encode("cockcodk0")) << endl;

}
