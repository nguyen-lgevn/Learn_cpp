/******************************************************************************
 * source: https://stackoverflow.com/question/46490403/variadic-template-as-parameters-to-stdfunction
 *****************************************************************************/

#ifndef __TEMPLATE_CLASS_H__
#define __TEMPLATE_CLASS_H__

template<typename Class, typename Return, typename ...Args>
class Caller
{
public:
    ~Caller() = default;

    Caller(Class& instance, Return(Class::*function)(Args ...))
    {
        calledFunction = [&instance, function](Args&&... args)
        {
            return (instance.*function)(std::forward<Args>(args) ...);
        };
    }

    Return operator() (Args&&... args)
    {
        return callerFunction(std::forward<Args>(args)...);
    }

private:
    std::function<Return(Args&&...)> callerFunction;

    Caller() = delete;
    Caller(const Caller&) = delete;
    Caller(Caller&&) = delete;
    Caller& operator=(const Caller&) = delete;
};

#endif
