#include <iostream>
#include <thread>
#include <iterator>

struct SquareComputer {
    // initialisation
    SquareComputer(int i, int *r) { input_value = i; return_value = r; }
    // thread function
    void operator()() { *return_value = input_value * input_value; }
    // thread local data
    int input_value;
    // pointer to variable shared between caller and callee
    int *return_value;
};

void main(int, char*[]) {
    int squares[3];
    std::thread t0(SquareComputer(1,squares+0));
    std::thread t1(SquareComputer(2,squares+1));
    std::thread t2(SquareComputer(3,squares+2));
    t0.join(); t1.join(); t2.join();
    std::copy(squares, squares+3, std::ostream_iterator<int>(std::cout,"\n"));
}
    