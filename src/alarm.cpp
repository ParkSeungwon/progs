#include<chrono>
#include<iostream>
#include<thread>
#include<cstdlib>
using namespace std;
using namespace chrono;

int main(int ac, char** av) {
	if(ac < 2) {
		cout << "usage : " << av[0] << " [minutes after alarm]" << endl;
		return 0;
	}
	int mn = atoi(av[1]);
	auto e = system_clock::now() + minutes(mn);
	auto tt = system_clock::to_time_t(e);
	cout << "will alarm you after " << mn << " minutes at " << ctime(&tt) << endl;
	this_thread::sleep_until(e);
	system("aplay /usr/lib/libreoffice/share/gallery/sounds/applause.wav");
}
