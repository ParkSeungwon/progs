#include<vector>
#include<iostream>
using namespace std;

vector<int> vec;
int indexes[] = {1, 1, 2, 2, 3, 3, 5};
int offset = 0;
int main() {
	for (int i = 0; i < sizeof(indexes)/sizeof(indexes[0]); i++) {
		vec.push_back(indexes[i]);
		offset += 1;
	}
	for(auto& a : vec) cout << a << ' ';
}
