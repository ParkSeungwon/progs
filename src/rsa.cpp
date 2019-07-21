#include<iostream>
#include<random>
#include<algorithm>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<atomic>
#define M 5000
using namespace std;

template <int N> class Prime 
{//generate N Prime numbers in compile time
public:
	unsigned arr[N]{};
	constexpr Prime() {
		int k=0;
		for(unsigned int i=2; k<N ;i++) {
			bool isPrime = true;
			for(int j=0; j<k; j++) {
				if(arr[j] > i/2) break;
				if(i % arr[j] == 0) {
					isPrime = false;
					break;
				}
			}
			if(isPrime) arr[k++] = i;
		}
	}
};

int lcm(int a, int b) 
{//least common multiple
	for(int i=1; ; i++) if(a*i % b == 0) return a*i;
}
		
long code(long m, long e, long K) 
{//m^e%K
	long sum = 1;
	for(long i=0; i<e; i++) {
		sum *= m;
		sum %= K;
	}
	return sum;
}

vector<unsigned int> stovi(string s)
{
	union {
		unsigned int n;
		unsigned char c[4];
	} u;
	vector<unsigned int> v;
	const char* p = s.data();
	for(int i=0; i < 4 - (s.size() % 4); i++) s += ' ';
	for(int i=0; i<s.size(); i+=4) {
		for(int j=0; j<4; j++) u.c[j] = *(p+i+j); 
		v.push_back(u.n);
	}
	return v;
}

string vitos(unsigned int n)
{
	union {
		unsigned int n;
		unsigned char c[4];
	} u;
	u.n = n;
	string s;
	s += u.c[0] + u.c[1] + u.c[2] + u.c[3];
	return s;
}
//atomic<int> using_cpu{0};
//mutex mtx;
//condition_variable cv;
vector<unsigned int> vi;
unsigned int decode(long m, long d, long K, int n)
{
//	static int cpu = thread::hardware_concurrency();
//	unsigned int r;
//	unique_lock<mutex> lck{mtx};
//	if(using_cpu > cpu) {
//		using_cpu++;
//		mtx.lock();
		vi[n] = code(m, d, K);
//		using_cpu--;
//	} else {
//		using_cpu++;
//		vi
//	cv.notify_one();
}

int main()
{//generate rsa key and encode sample
	Prime<M> prime;
	auto it = lower_bound(prime.arr, prime.arr+M, 10000);
	uniform_int_distribution<> di(it - prime.arr, M-1);
	random_device rd;

	int p = prime.arr[di(rd)];
	int q = prime.arr[di(rd)];
	long K = p * q;
	long phi = lcm(p-1, q-1);
	long i;
	for(i=di(rd); phi % prime.arr[i] == 0; i++);
	int e = prime.arr[i];
	for(i=1; (phi * i + 1) % e; i++);
	long d = (phi * i + 1) / e;

	cout << "p = " << p << ", q = " << q << ", phi = " << phi << endl;
	cout << "K = " << K << ", e = " << e << " , d = " << d << endl;
	cout << "enter message to encode" << endl;
	string s;
	cin >> s;//reuse
	vector<long> v;
	for(auto& a : stovi(s)) v.push_back(code(a, e, K));
	for(auto& a : v) cout << "encoded to " << a << ' ';

	vi.resize(v.size());
	thread threads[v.size()];
	for(int i=0; i<v.size(); i++) threads[i] = thread(decode, v[i], d, K, i);
	for(int i=0; i<v.size(); i++) threads[i].join();
	s.clear();
	for(auto& a : vi) s += vitos(a);
	cout << endl << "decoded to " << s << endl;
}



