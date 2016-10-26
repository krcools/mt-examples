#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#define NB 1000

struct BurgerStack {
    void make() {
        {
            std::lock_guard<std::mutex> lk(mutex);
            burgers.push_back(1);
        }
        cond.notify_one();
    }
    void eat() {
        std::unique_lock<std::mutex> lk(mutex);
        if( burgers.empty() ) std::cout << "I'm hungry!\n";
        while( burgers.empty() ) cond.wait(lk);
        burgers.pop_back();
    }
    std::vector<int> burgers;
    std::mutex mutex;
    std::condition_variable cond;
} stack;

struct Customer { void operator()(){ for(int i=0; i<NB; ++i) stack.eat(); } };
struct Chef     { void operator()(){ for(int i=0; i<NB; ++i) stack.make();} };

void main(int, char*[]) {
    std::thread customer((Customer()));
    std::thread chef((Chef()));
    
    customer.join(); chef.join();
    std::cout << "Burgers left: " << stack.burgers.size() << std::endl;
}