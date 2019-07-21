#include<iostream>
#include<cmath>
typedef unsigned long UL;
using namespace std;

bool is_beautiful(UL base, UL n) {
	if(n == 1) return true;
	if(n % base != 1) return false;
	return is_beautiful(base, n / base);
}

int main()
{
	UL N, n;
	cin >> N;
	for(int j=0; j<N; j++) {
		cin >> n;
		cout << "Case #" << j+1 << ": ";
		UL i=2;
		while(!is_beautiful(i, n)) {
			if(i > sqrt(n)) i = n-2;
			i++;
		}
		cout << i << endl;
	}
}
