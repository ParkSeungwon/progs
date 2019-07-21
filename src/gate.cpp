#include<iostream>
#include<algorithm>
using namespace std;

int fact(int r) {
	int sum = 1;
	for(int i=1; i<=r; i++) sum *= i;
	return sum;
}
int nCr(int n, int r) {
	if(r > n) return 0;
	return fact(n) / fact(r) / fact(n-r);
}
int main()
{
	int M, N;
	cin >> N >> M;
	int k[M];
	for(int i=0; i<M; i++) cin >> k[i];
	sort(k, k+M);
	int even=0, odd=0;
	for(int i=0; i<M; i++) k[i] % 2 ? odd++ : even++;
	cout <<  nCr(M, N) - nCr(even, N) - nCr(odd, N);
}


