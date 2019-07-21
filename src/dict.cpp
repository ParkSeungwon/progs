#include<vector>
#include<fstream>
#include<iostream>
#include<algorithm>
#include<regex>
#include<random>
#include"matrix.h"
using namespace std;

vector<string> no {"there is no such word"};

template <typename T> T find(const T& a, const T& b, string s) 
{// T should be pointer or iterator that can handle * operator
	if(b <= a + 1) {
		if(*a == s) return a;
		else return no.begin();
	} else {
		int mid = (b - a) / 2;
		if(*(a + mid) == s) return a + mid;
		else if(*(a + mid) < s) return find(a + mid, b, s);
		else return find(a, a + mid, s);
	}
}

vector<string> find_match(const vector<string>& dict, string regexp) 
{
	vector<string> v;
	regex e{regexp};
	for(auto it = dict.begin(); it != dict.end(); it++)
		if(regex_match(*it, e)) v.push_back(*it);
	return v;
}

string get_regex(Matrix<char>& mat, int x1, int y1, int x2, int y2)
{//get string for crossword puzzle 
	string e;
	if(x1 == x2) {
		for(int y=y1; y<=y2; y++) {
			if(mat[x1][y] == ' ') e += '.';
			else e += mat[x1][y];
		}
	} else {
		for(int x=x1; x<=x2; x++) {
			if(mat[x][y1] == ' ') e += '.';
			else e += mat[x][y1];
		}
	}
	return e;
}

int main(int ac, char** av)
{
	if(ac < 3) {
		cout << "Usage : " << av[0] << " width height" << endl;
		return 0;
	}
	int w = atoi(av[1]);
	int h = atoi(av[2]);
	Matrix<char> mat{w, h};//start from (1,1)
	for(int x=1; x<=w; x++) for(int y=1; y<=h; y++) mat[x][y] = ' ';
	vector<string> v;
	{
		ifstream f{"/usr/share/dict/american-english"};
		string s;
		while(getline(f, s)) v.push_back(s);
	}

	int x1, y1, x2, y2;
	while(true) {
		cout << "line carefully" << endl;
		cin >> x1 >> y1 >> x2 >> y2;
		string e = get_regex(mat, x1, y1, x2, y2);

		vector<string> candidate = find_match(v, e);
		int i = -1;
		while(i == -1) {
			shuffle(candidate.begin(), candidate.end(), random_device());
			for(int j=0; j<10 && j<candidate.size(); j++) 
				cout << j+1 << ". " << candidate[j] << endl;
			cout << "select 0 to go back, -1 to reshuffle, -2 to quit";
			cin >> i;
		} 
		if(!i) continue;
		else if(i == -2) break;

		//put string to matrix
		if(x1 == x2) for(int y=y1; y<=y2; y++) mat[x1][y] = candidate[i-1][y-y1]; 
		else for(int x=x1; x<=x2; x++) mat[x][y1] = candidate[i-1][x-x1];
		cout << mat;
	}
	ofstream f("mat.dat");
	for(int y=1; y<=h; y++) {
		for(int x=1; x<=w; x++) f << mat[x][y];
		f << endl;
	}
}
