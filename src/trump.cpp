#include<iostream>
#include<algorithm>

int before[13], after[13];

int idx(int n) {
	for(int i=0; i<13; i++) if(before[i] == n) return i;
}

int translate(char c) {
	switch(c) {
		case 'A': return 14;
		case 'J': return 11;
		case 'Q': return 12;
		case 'K': return 13;
		case '1': return 10;
		default: return c - '0';
	}
}

int max = 0;
void count_ascend(int count, int* p, int current_big) {
	if(p == after + 13) {
		if(max < count) max = count;
		return;
	}
	count_ascend(count, p+1, current_big);
	if(*p > current_big) count_ascend(count+1, p+1, *p);
}

int main()
{
	char c, garbage;
	for(int i=0; i<13; i++) {
		std::cin >> c;
		if(c == '1') std::cin >> garbage;
		before[i] = translate(c);
	}
	for(int i=0; i<13; i++) {
		std::cin >> c;
		if(c == '1') std::cin >> garbage;
		after[i] = translate(c);
	}
	for(int i=0; i<13; i++) after[i] = idx(after[i]);
	count_ascend(0, after, 0);
	std::cout << max << std::endl;
}
