#include<string>
#include<iostream>
#include<sstream>
#include<regex>
#include<mysqldata.h>
using namespace std;

int main(int ac, char** av) 
{
	if(ac < 6) {
		cout << av[0] << " [host] [user] [password] [database] [table]" << endl;
		return 0;
	}

	SqlQuery sq;
	sq.connect(av[1], av[2], av[3], av[4]);
	
	
	//if table exist->print in csv form
	for(auto& a : sq.show_tables()) if(a == av[5]) {
		sq.select(av[5]);

		int i=0;
		auto vp = sq.desc();
		while(i < vp.size() - 1) cout << vp[i++].first << ',';
		cout << vp[i].first << endl;
		for(auto& a : sq) {
			for(i=0; i < a.size()-1; i++) cout << a[i] << ',';
			cout << a[i] << endl;
		}
		return 0;
	}
	
	
	//if table doesn't exist, create it from standard input or pipe from csv file
	auto& structure = sq.desc();//structure information to create table 
	
	string s;
	vector<string> v;
	vector<vector<string>> vv;
	
	while(getline(cin, s)) {//populate vv
		if(s.back() == ',') s.push_back(' ');
		stringstream ss;
		ss << s;
		while(getline(ss, s, ',')) v.push_back(s);
		vv.push_back(v);
		v.clear();
	}

	regex INT{R"([\+-]?\d+)"};
	regex FLOAT{R"([\+-]?\d+\.\d+)"};
	for(int j=0; j<vv[0].size(); j++) {
		int ic=0, fc=0, sc=0;//to find whether this column is int of float or char
		for(int i=1; i<vv.size(); i++) {
			try {
				if(regex_match(vv[i][j], INT)) ic++;
				else if(regex_match(vv[i][j], FLOAT)) fc++;
				else sc++;
			} catch(exception& e) { 
				cout << e.what();
			}
		}
		if(ic >= fc && ic >= sc) s = "INT";
		else if(fc >= ic && fc >= sc) s = "FLOAT";
		else s = "TEXT";
		structure.push_back({vv[0][j], s});
	}
	for(auto& a : structure) cout << a.first << ':' << a.second << endl;
	sq.create_table(av[5]);
	for(int i=1; i<vv.size(); i++) sq.insert(vv[i]);
}

