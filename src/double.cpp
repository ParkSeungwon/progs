#include<iostream>
#include<thread>
#include<mutex>
#include<chrono>
using namespace std;
using namespace chrono;

recursive_mutex mtx;
int winner;
once_flag flag;

void win(int n) { winner = n; cout << " I won " << endl; }
struct Fctor {
	void operator()(int& i) { cout << "in fctor " << i++ << endl; }
};

int f(int n)
{
	if(n == 1) {
		cout << endl;
		call_once(flag, win, 3);
		return 1;
	}
	mtx.lock();
	int r = n*f(n-1);
	cout << r << ' ';
	mtx.unlock();
	return r;
}		

int main()
{
	int k = 0;
	thread th1(Fctor{}, ref(k));
	thread th[10];
	th[1] = move(th1);
	for(int i=9; i>1; i--) th[i] = thread(f, i);
	for(int i=1; i<10; i++) th[i].join();
	cout << " k is " << k << endl;
	cout << "cpu = " << thread::hardware_concurrency() << endl;;
}
