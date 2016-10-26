#include <iostream>
#include <thread>
#include <future>
#include <chrono>

struct SquareComputer {
    SquareComputer(int j) { i = j; }
    int operator()() {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return i*i;
    }
    int i;
};

int squareComputer() { return 2*2; }

void main(int, char*[]) {
	SquareComputer sq{ 2 };
	std::packaged_task<int()> task{ sq };
	std::future<int> value = task.get_future();
	std::thread t{ std::move(task) };
	std::cout << "Try to get value..." << std::endl;
    std::cout << value.get() << std::endl;
	std::cout << "Got value!" << std::endl;
	t.join();
}
