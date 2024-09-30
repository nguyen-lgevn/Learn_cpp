#include <iostream>
#include "Singleton.h"
#include "CQueue.h"
//#include "dispatcher.h"

template<typename Class, typename Return, typename... Args>
class Caller {
private:
    std::function<Return(Args...)> callerFunction;

    Caller() = delete;
    Caller(const Caller&) = delete;
    Caller(Caller&&) = delete;
    Caller& operator=(const Caller&) = delete;

public:
    ~Caller() = default;

    Caller(Class& instance, Return(Class::*function)(Args...))
    {
        callerFunction = [&instance, function](Args&&... args)
        {
            return (instance.*function)(std::forward<Args>(args)...);
        };
    }

    Return operator() (Args... args)
    {
        return callerFunction(args...);
    }
};


int main()
{
    std::cout << "Entering main()" << std::endl;

    std::cout << "Leaving main()" << std::endl;
    return 0;
}
