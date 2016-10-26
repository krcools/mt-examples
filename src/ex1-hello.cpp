#include <iostream>  
#include <string>
#include <thread>

struct Worker {
    // message to be print is set in the constructor
    Worker(const std::string &str) { msg = str; }
    // function executed as a separate thread
    void operator()() { std::cout << "Worker: " << msg << std::endl; }
    // thread local data
    std::string msg;
};
 
void main(int argc, char* argv[])  // main program thread
{  
    std::thread thread(Worker("Hello, world!"));
    thread.join();
} 
