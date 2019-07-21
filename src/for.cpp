#include<iostream>
#include<cstdio>
using namespace std;

void pr(int n)
{
	int line1[n], line2[n-1];
	for(int i=0; i<n; i++) {
		printf("%d ", 2*i + 1);
		line1[i] = 2*i + 1;
	}
	printf("\n");
	for(int i=0; i<n-1; i++) {
		printf(" %d", 2*i + 2);
		line2[i] = 2*i + 2;
	}
	printf("\n");
	for(int j=n-2; j>0; j--) {
		for(int i=0; i<n-j; i++) printf(" ");
		for(int i=0; i<j; i++) {
			int k = line1[i] + line1[i+1] + line1[i+2] + line2[i] + line2[i+1];
			printf("%d ", k);
			line1[i] = line2[i];
			line2[i] = k;
		}
		printf("\n");
	}
}
int main()
{
	pr(5);
}
