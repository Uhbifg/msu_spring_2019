#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

const std::uint64_t MAX = 1000000;
std::mutex mutex;
std::condition_variable ready;
std::uint64_t i = 0;

void ping() {
    std::unique_lock<std::mutex> lock(mutex);
    while (i < MAX) {
        while (i % 2)
            ready.wait(lock);
        std::cout << "ping" << std::endl;
        i++;
        ready.notify_one();
    }
}


void pong() {
    std::unique_lock<std::mutex> lock(mutex);
    while (i < MAX) {
        while (!(i % 2))
            ready.wait(lock);
        std::cout << "pong" << std::endl;
        i++;
        ready.notify_one();
    }
}

int main() {
    std::thread t1(ping);
    std::thread t2(pong);
    t1.join();
    t2.join();
    return 0;
}