#include <iostream>
#include <chrono>
#include <mutex>
#include <thread>

std::mutex mtx;

void foo()
{
    while (1) {
        std::lock_guard<std::mutex> lk(mtx);
        std::cout << "Thread " << std::this_thread::get_id() << " is running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void bar()
{
    while (1) {
        std::lock_guard<std::mutex> lk(mtx);
        std::cout << "Thread " << std::this_thread::get_id() << " is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

int main(int argc, char **argv)
{
    std::thread t1(foo);
    std::thread t2(bar);

    std::cout << "Start" << std::endl;

    t1.detach();
    t2.detach();

    while (1)
    {
        std::cout << "Main thread running..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }

    std::cout << "End" << std::endl;
    return 0;
}
