#include <iostream>  
#include <string>
#include <thread>

inline void print(const std::string &s){
    for(std::string::const_iterator b = s.begin(), e = s.end(); b!=e; ++b)
    std::cout << *b << std::flush;
}

struct Worker {
    Worker(const std::string &str) { msg = str; }
    void operator()() { print(msg); }
    std::string msg;
};
 
void main(int argc, char* argv[])
{  
    std::thread t0(Worker("Hello, Mercury\n")), t1(Worker("Hello, Venus\n")),
                  t2(Worker("Hello, Earth\n")), t3(Worker("Hello, Mars\n"));
    t0.join(); t1.join(); t2.join(); t3.join();
} 

