/*****************************************************************************
 *  source: https://stackoverflow.com/questions/30425772/c-11-calling-a-function-periodically
 *
 * ***************************************************************************/

#ifndef __CALLBACKTIMER_H__
#define __CALLBACKTIMER_H__

#include <thread>
#include <chrono>
#include <atomic>
#include <iostream>

namespace Timer {
class CallbackTimer {
public:
    CallbackTimer():_execute(false){}
    ~CallbackTimer() {
        if (_execute.load(std::memory_order_acquire))
        {
            stop();
        }        
    }

    void stop()
    {
        std::cout << __FUNCTION__ << std::endl;
        //_execute.store(false, std::memory_order_release);
        if (_thd.joinable())
        {
            _thd.join();
        }
    }

    void start(int interval, std::function<void(void)> func)
    {
        if (_execute.load(std::memory_order_acquire)) {
            stop();
        }
        std::cout << "Start run...\n";
        _execute.store(true, std::memory_order_release);
        std::cout << _execute.load() << std::endl;
        _thd = std::thread([this, interval, func]()
                {
                    std::cout << _execute.load() << std::endl;
                    while (_execute.load(std::memory_order_acquire))
                    {
                        std::cout << "....\n";
                        func();
                        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
                    }
                });
    }

    bool is_running() const noexcept {
        return (_execute.load(std::memory_order_acquire)) && _thd.joinable();
    }

private:
    std::atomic<bool> _execute;
    std::thread _thd;
};
} // Timer

#endif
