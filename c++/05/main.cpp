#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

const int N = 500000;
bool flag = true;
std::condition_variable c;
std::mutex m;

void ping(){
    std::unique_lock<std::mutex> lock(m);
    for(int i = 0; i < N; i++){
        c.wait(lock, [](){
            return flag;
        });
        std::cout << "ping" << std::endl;
        flag = false;
        c.notify_one();
    }
}

void pong(){
    std::unique_lock<std::mutex> lock(m);
    for(int i = 0; i < N; i++){
        c.wait(lock, [](){
            return !flag;
        });
        std::cout << "pong" << std::endl;
        flag = true;
        c.notify_one();
    }
}

int main() {
    std::thread thread1(ping);
    std::thread thread2(pong);
    thread1.join();
    thread2.join();
    return 0;
}