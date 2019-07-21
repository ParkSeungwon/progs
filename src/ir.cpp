#include<iostream>
#include<iomanip>
#include"irrational.h"
using namespace std;

int main()
{
	auto a = Root(5, 2) + 3;
	int cs, n;
	cin >> cs;
	for(int j=0; j<cs; j++) {
		auto c = a;
		cin >> n;
		for(int i=0; i<n-1; i++) c = c * a;
		int b = c.approx();
		cout << "Case #" << j+1 << ": ";
		cout << setw(3) << setfill('0') << b % 1000 << endl;
	}
}
