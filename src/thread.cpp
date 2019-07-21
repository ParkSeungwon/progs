#include<thread>
#include<iostream>
using namespace std;
thread_local int fd = 0;
void g() {
	cout << fd << "in g" << endl;
}
void f(int k) {
	while(1) {
	this_thread::sleep_for(1s);
	fd++;
	cout << fd << endl;
	thread th1{g};
	th1.join();
	}
}

int main(int ac, char **av)
{
	{	
	thread th{f, 3};
	thread th2{f, 7};
	th.join();
	th2.join();
	}
	this_thread::sleep_for(3s);
}

