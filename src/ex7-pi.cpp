#include <iostream>
#include <thread>
#include <mutex>

const int N = 1000000, T = 8; // number of evaluations, number of threads
const double PI25DT = 3.141592653589793238462643; // for comparison
std::mutex write_to_result_mutex; // associated to write access to pi

struct Worker {
    Worker(int i, double *p) { id = i; pi = p; } // initialisation
    void operator()() {                          // thread function
        double mypi = 0.0, h = 1.0 / N;
        for(int i = id + 1; i <= N; i += T)
            { double x = h * (i - 0.5); mypi += h * (4 / (1+x*x)); }
        std::lock_guard<std::mutex> lk(write_to_result_mutex);
        *pi += mypi;
    }
    int id; double *pi;                          // thread local data
};

void main(int, char*[]) {
	double pi = 0.0;
	std::thread thread[T];
	for (int i = 0; i < T; ++i) thread[i] = std::thread(Worker(i, &pi));
	for (int i = 0; i < T; ++i) thread[i].join();
    std::cout << "pi appr. " << pi << "..., error: " << pi-PI25DT << std::endl;
}
