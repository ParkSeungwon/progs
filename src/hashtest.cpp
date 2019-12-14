#include<cstring>
#include<iostream>
using namespace std;

int hash1(const char *p) {
	int sum = 0;
	while(*p) sum += *p++;
	return sum % 256;
}

int main() {
	char p[100] = "give him 1000 dollars";
	cout << hash1(p);//해쉬값 251
	p[9] = '2';
	cout << hash1(p);//해쉬값 252
	strcpy(p, "give him 182222000 dollars");
	cout << hash1(p);//해쉬값 251
}

