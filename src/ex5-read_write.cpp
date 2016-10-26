#include <iostream>
#include <string>
#include <vector>
#include <thread>  
#include <mutex>
#include <shared_mutex> // Officially only since C++17!!!

#define NUMREADERS 10
std::string data = "Original Message";
std::vector<std::string> copies(NUMREADERS);
std::shared_mutex data_mutex;

struct Reader {
    Reader(int i) { id = i; }
    void operator()() {
        std::shared_lock<std::shared_mutex> lk(data_mutex);
        copies[id] = data;
    }
    int id;
};
struct Writer {
    void operator()() {
        std::unique_lock<std::shared_mutex> lk(data_mutex);
        data = "A new and better message!";
    }
};
void main(int argc, char* argv[])
{  
	std::thread threads[NUMREADERS+1];
	threads[0] = std::thread(Writer());
	for (int i = 1; i < NUMREADERS + 1; ++i)
		threads[i] = std::thread(Reader(i));
	for (int i = 0; i < NUMREADERS + 1; ++i)
		threads[i].join();
    for(int i = 0; i < copies.size(); ++i)
        std::cout << "[" << i << "]: " << copies[i] << std::endl;
} 
