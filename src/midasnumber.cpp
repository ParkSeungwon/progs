#include<iostream>
using namespace std;

bool is_prime(int n) {
	for(int i=2; i<=n/2; i++) if(n % i == 0) return false;
	return true;
}

int midas(int n) {
	for(int i=n; i>1; i--) if(is_prime(i) && n%i == 0) return i;
}


int main()
{
	int M, N, R=0;
	cin >> N >> M;
	for(int i=2; i<=N; i++) {
		if(midas(i)<=M) R++;
	}
	cout << R;
}

