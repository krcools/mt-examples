#include <iostream>  
#include <string>
#include <thread>  

struct Worker {
    Worker(const std::string &str) { msg = str; }
    void operator()() {
        // retrieve thread id
        std::thread::id myid = std::this_thread::get_id();
        std::cout << "[" << myid << "]: " << msg << std::endl; }
    std::string msg;
};
 
void main(int argc, char* argv[])  // main program thread
{  
    std::thread thread(Worker("Hello, world!"));
    thread.join();
} 