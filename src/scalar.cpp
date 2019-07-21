#include<vector>
#include<iostream>
#include<string>
#include<sstream>
#include<algorithm>
#include<set>
#include<functional>
using namespace std;

class Customer
{
public:
	Customer(string s) {
		stringstream ss;
		ss << s;
		int sz;
		ss >> sz;
		for(int i=0; i<sz; i++) {
			int a, b;
			ss >> a >> b;
			likes.push_back(a * (b ? 1 : -1));
		}
	}

	vector<int> likes;
	bool operator<(const Customer& r) const {
		return likes.size() < r.likes.size();
	}
};

vector<int> milk;
bool ended = false;
int T, m, c;

template <typename T> void batch(T it, T end)
{
	if(ended) return;
	if(it == end) {
		int arr[m] {0,};
		for(auto& a : milk) if(a>0) arr[a-1] = 1;
		for(auto& a : arr) cout << a << ' ';
		ended = true;
		return;
	}

	for(auto& a : it->likes) {
		if(find(milk.begin(), milk.end(), a) == milk.end() && 
				find(milk.begin(), milk.end(), -a) == milk.end()) {
			milk.push_back(a);
			batch(it+1, end);
			milk.pop_back();
		}
	}
}

int main()
{
	cin >> T;//test case
	for(int i=0; i<T; i++) {
		vector<Customer> v;
		cin >> m >> c;//milk shake, customer
		string g;
		getline(cin, g);
		for(int i=0; i<c; i++) {
			string s;
			getline(cin, s);
			v.push_back(Customer(s));
		}

		sort(v.begin(), v.end());
		cout << "Case #" << i+1 << ": ";
		batch(v.begin(), v.end());
		if(!ended) cout << "IMPOSSIBLE";
		ended = false;
		milk.clear();
		cout << endl;
	}

}
