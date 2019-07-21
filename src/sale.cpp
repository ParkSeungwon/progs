#include<iostream>
using namespace std;

int N;
int minv = 100000000;
void calc(int* p, int* end, int sum) {
	if(p == end) {
		if(sum < minv) minv = sum;
		return;
	}
	if(p == end - 1) {
		sum += *p;
		if(minv > sum) minv = sum;
		return;
	}
	if(p == end - 2) {
		sum += *p + *(p+1);
		if(minv > sum) minv = sum;
		return;
	}
	calc(p + 1, end, sum + *p);
	calc(p + 2, end, sum + *p + *(p+1));
	sum += *p + *(p+1) + *(p+2);
	sum -= *p < *(p+1) ? 
		(*p < *(p+2) ? *p : *(p+2)) : (*(p+1) < *(p+2) ? *(p+1) : *(p+2));
	calc(p + 3, end, sum);
}

int main()
{
	cin >> N;
	int price[N];
	for(int i=0; i<N; i++) cin >> price[i];
	calc(price, price+N, 0);
	cout << minv;
}

