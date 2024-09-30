#include "Timer.h"

using namespace Utils;

Stoppable::Stoppable():
    futureObj(exitSignal.get_future())
{
}

void Stoppable::operator()()
{
    run();
}

bool Stoppable::stopRequeset()
{
    if (futureObj.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
        return false;
    return true;
}

void Stoppable::stop()
{
    exitSignal.set_value();
}

void Timer::run()
{
    while (stopRequeset() == false)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
