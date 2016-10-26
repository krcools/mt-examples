#include <iostream>  
#include <string>
#include <thread>
#include <mutex>

// associate this mutex (shared by all threads) to acces to std::cout
std::mutex cout_mutex;


inline void print(const std::string &s){
    for(std::string::const_iterator b = s.begin(), e = s.end(); b!=e; ++b)
    std::cout << *b << std::flush;
}

struct Worker {
    Worker(const std::string &str) { msg = str; }
    void operator()() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        print(msg);
    }
    std::string msg;
};
 
void main(int argc, char* argv[])
{  
    std::thread t0(Worker("Hello, Mercury\n")), t1(Worker("Hello, Venus\n")),
                  t2(Worker("Hello, Earth\n")), t3(Worker("Hello, Mars\n"));
    t0.join(); t1.join(); t2.join(); t3.join();
} 

