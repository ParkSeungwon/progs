#include<iostream>
#include<thread>
using namespace std;

int turn = 0;
void f(int pid) {
	while(1) {
		while(turn != pid) ;
		cout << pid << " in critical section" << endl;
		turn = !pid;
	}
}

int main()
{
	thread t1{f, 0};
	f(1);
}
