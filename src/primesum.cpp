#include<iostream>
using namespace std;

bool is_prime(int n) {
	for(int i=2; i<=n/2; i++) if(n % i == 0) return false;
	return true;
}

int main()
{
	int M, N, R=0;
	cin >> M >> N;
	for(int i=M; i<=N; i++) if(is_prime(i)) R += i;
	cout << (!R ? -1: R);
}
