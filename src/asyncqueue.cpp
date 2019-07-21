#include<iostream>
#include<functional>
#include<chrono>
#include "asyncqueue.h"
using namespace std;

template <typename T> 
AsyncQueue<T>::AsyncQueue(function<T()> provider, function<void(T)> consumer)
{
	this->provider = provider;
	this->consumer = consumer;
	thi = thread(&AsyncQueue::provide, this);
	tho = thread(&AsyncQueue::consume, this);
}

template <typename T> AsyncQueue<T>::~AsyncQueue()
{
	finish = true;
	thi.join();
	tho.join();
}

template <typename T> void AsyncQueue<T>::provide()
{///recv->functor->q->notify to sendf
	while(!finish) push_back(provider());
}
	
template <typename T> void AsyncQueue<T>::consume()
{
	unique_lock<mutex> lck{mtx, defer_lock};
	while(!finish) {
		lck.lock();
		while(q.empty()) cv.wait(lck);
		consumer(q.front());
		q.pop_front();
		lck.unlock();
	}
}

template <typename T> void AsyncQueue<T>::push_back(T s)
{///asynchronous send, ->sendf()
	unique_lock<mutex> lck{mtx};
	q.push_back(s);
	lck.unlock();
	cv.notify_all();
}

struct F {
	int n = 0;
	int operator()() {
		this_thread::sleep_for(chrono::seconds(1));
		return n++;
	}
} f;

void g(int n) {
	cout << "consuming " << n << endl;
}

int main()
{
	AsyncQueue<int> q{f, g};
	int n;
	while(cin >> n) q.push_back(n);
}
