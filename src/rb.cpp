#include<iostream>
using namespace std;

int count_node(int h) 
{
	int sum = h;
	for(int i=1; i<=h-2; i++) sum += count_node(i);
	return sum;
}

int count_minimum_node(int h) { return count_node(h+1); }
int main(int c, char** v)
{
	cout << count_minimum_node(atoi(v[1])) << endl;
}

