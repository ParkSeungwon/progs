#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;

int main()
{
	vector<int> v{4,3,7,1,5};
	make_heap(v.rbegin(), v.rend(), greater<int>());
	for(auto& a : v) cout << a << ' ';
	cout << endl;
	v.pop_back();
	for(auto& a : v) cout << a << ' ';
	cout << endl;
	v.push_back(9);
	make_heap(v.rbegin(), v.rend(), greater<int>());
	for(auto& a : v) cout << a << ' ';
	cout << endl;
}
