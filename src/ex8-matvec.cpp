#include <iostream>
#include <vector>
#include <thread>

const int M = 100, N = 80, T = 8;       // number of rows, columns, threads
std::vector<double> A(M*N), x(N), y(M); // shared storage for matrix and vects

struct Worker {
    Worker(int i)
    { id=i; lo=std::floor((i+0.0)*M/T); hi=std::floor((i+1.0)*M/T)-1; }
    void operator()() {
        for(int i=lo; i<=hi; ++i) for(int j=0; j<N; ++j) y[i] += A[i*N+j]*x[j];
    }
    int id, lo, hi;
};

void main(int, char*[]) {
    
    for(int i=0; i<M*N; ++i) A[i] = std::rand() / double(RAND_MAX);
    for(int i=0; i<N; ++i)   x[i] = std::rand() / double(RAND_MAX);

	std::thread threads[T];
	for (int i = 0; i < T; ++i) threads[i] = std::thread(Worker(i));
	for (int i = 0; i < T; ++i) threads[i].join();
}
