#include <thread>
#include <chrono>
#include <iostream>

struct Worker {
    Worker(char *d, int s) :
        data(d), size(s) {}
    void operator()() {
        unsigned long long myCounter = 100000000;
        while(--myCounter)
            for(int i=0; i<size; ++i)
                ++data[i];
    }
    char* data;
    int   size;
};

#define N 1000
//#define N 10
void main() {
    char data0[N], data1[N];
	std::chrono::time_point<std::chrono::steady_clock> t0, t1;
	t0 = std::chrono::steady_clock::now();
    std::thread A(Worker(data0,10));
    std::thread B(Worker(data1,10));
	t1 = std::chrono::steady_clock::now();
	std::chrono::duration<double> dt = t1 - t0;
    A.join(); B.join();
	std::cout << "Elapsed seconds: " << dt.count() << std::endl;
}
