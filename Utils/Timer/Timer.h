/******************************************************************************
 * source: https://stackoverflow.com/questions/14650885/how-to-create-timer-events-using-c-11
 *
 *****************************************************************************/
#ifndef __TIMER_H__
#define __TIMER_H__

#include <functional>
#include <chrono>
#include <future>
#include <cstdio>
#include <type_traits>

namespace Utils {

class Stoppable {
    std::promise<void> exitSignal;
    std::future<void> futureObj;

public:
    Stoppable();
    Stoppable(Stoppable && rhs):
        exitSignal(std::move(rhs.exitSignal)),
        futureObj(std::move(rhs.futureObj))
    {
    }

    Stoppable& operator=(Stoppable&& rhs)
    {
        exitSignal = std::move(rhs.exitSignal);
        futureObj = std::move(rhs.futureObj);
        return *this;
    }

    virtual void run() = 0;
    void operator()();

    bool stopRequeset();

    void stop();
};

class Timer: public Stoppable { 
public:
    void run() override;

    template<class callable, class Functor, class ... arguments>
    void setTimer(int timeout, bool async, callable& obj, Functor&& f, arguments&& ... args)
        {
            typename std::result_of<decltype(&f)(arguments...)>::type f;
            // std::function<typename std::result_of<decltype(&f)(arguments...)>::type()> func;
            /*
            std::function<typename std::result_of<&f>::type()> task(std::bind(std::forward<callable>(f), obj, std::forward<arguments>(args)...));

            if (async)
            {
                std::thread([timeout, task](){
                        std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
                        task();
                        }).detach();
            }
            else
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(timeout));
                task();
            }
            */
        }
};

} // Utils
#endif
