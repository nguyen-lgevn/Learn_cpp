#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

mutable std::atomic_flag mLock = ATOMIC_FLAG_INIT;

void little_sleep(std::chrono::microseconds us)
{
    auto start = std::chrono::high_resolution_clock::now();
    auto end = start + us;
    /*
    do {
        std::this_thread::yield();
    } while (std::chrono::high_resolution_clock::now() < end);
    */
    for (unsigned int i = 0; mLock.test_and_set(std::memory_order_acquire); ++i)
    {
        if (i%1000 == 0)
            std::this_thread::yield();
    }
    mLock.clear(std::memory_order_release);
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    little_sleep(std::chrono::microseconds(100));
    
    auto elapsed = std::chrono::high_resolution_clock::now() - start;
    std::cout << "waited for " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << " microseconds\n";
}
