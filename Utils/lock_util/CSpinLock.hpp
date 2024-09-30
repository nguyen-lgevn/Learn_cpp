#ifndef __CSPINLOCK_HPP__
#define __CSPINLOCK_HPP__

#include <atomic>
#include <thread>

class CSpinLock {

public:
    CSpinLock() {}
    ~CSpinLock() {}

    void lock() const 
    {
        for (unsigned int i = 0; mLock.test_and_set(std::memory_order_acquire) ; ++i)
        {
            if (i % 1000 == 0)
            {
                std::this_thread::yield();
            }
        }
    }

    void unlock() const 
    {
        mLock.clear(std::memory_order_release);
    }

private:
    mutable std::atomic_flag mLock = ATOMIC_FLAG_INIT;
    constexpr int MAX_SPIN_COUNT = 1000;
};

#endif
