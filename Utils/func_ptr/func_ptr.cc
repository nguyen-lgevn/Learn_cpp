#include <iostream>
#include <map>
#include <functional>
#include <binders.h>
#include <thread>
#include <chrono>

#define CAST_FUNC(clsName, func) reinterpret_cast<>(&clsName::func)

/*
class FooDispatcher {
public:
    FooDispatcher(){}
    virtual ~FooDispatcher(){}
    typedef int (FooDispatcher::*MsgHandler) (int cmd, int instId, void* pMsg);
    virtual int DispatcherHandle(int cmd, int instId, void* pMsg);
    virtual void regHandler(int cmd, FooDispatcher::MsgHandler fpHandle);
    virtual void unregHandler();
protected:
    std::map<int, FooDispatcher::MsgHandler> m_msgHandle;
};

class FooController: public FooDispatcher 
{
public:
    FooController(){}
};
*/

class Foo {
public:
    void foo1() {std::cout << __FUNCTION__ << std::endl;}
    void foo2(int a) {std::cout << __FUNCTION__ << " " << a << std::endl;}
    void foo4(int a, int b) { std::cout << a+b << std::endl;}
    void foo3(int a, std::string str) {std::cout << "Number: " << a << " string: " << str << std::endl;}

    int foo5(int a) {std::cout << __FUNCTION__ << " " << a << std::endl;}
};

class Bar {
public:
    template<class cls, typename func, typename ...Args>
        void callFunc(std::function<func>& f) {
            f();
        }
};

class EventHandler {
public:
    //void addHandler(std::function<void(int)> callback, int arg)
    //{
    //    callback(arg);
    //}

    //template<typename... Args>
    //void addHandler(std::function<void(Args...)> const &callback, Args&&... args)
    //{
    //    callback(std::forward<Args>(args)...);
    //}
    //
    //template<typename T, typename... Args>
    //void startTimer(int seconds, std::function<T(Args...)> const &callback, Args&&... args)
    //{
    //    while (1)
    //    {
    //        callback(std::forward<Args>(args)...);
    //        std::this_thread::sleep_for(std::chrono::seconds(seconds));
    //    }
    //}

    template<typename T, typename... Args>
    void addHandler(std::function<T(Args...)> const &callback, Args&&... args)
    {
        //std::thread th(&EventHandler::startTimer<T, Args...>, this,  seconds , callback, args...);
        //th.detach();
        m_lstCallback[id] = callback;
    }

private:
    std::map<int, std::function<void()> > m_lstCallback;
};
//template<> void EventHandler::addHandler<void>(std::function<void()>);
//template<int> void EventHandler::addHandler<int>(std::function<void(int)>, int);

template<typename T, typename R, typename... Args>
R callFunc(T& obj, R (T::*mf)(Args...), Args&& ... args) {
    return (obj.*mf)(std::forward<Args>(args)...);
}

template<typename T, typename R>
R callFunc(T& obj, R (T::*mf)(void)) {
    return (obj.*mf)();
}

int main()
{

    Foo f;
//    Bar b;
//    b.callFunc(std::function<void(const Foo&, int)>(&Foo::foo2));
    EventHandler handler;
    std::function<void(int)> func = std::bind(&Foo::foo2, f, std::placeholders::_1);
    std::function<void()> func1 = std::bind(&Foo::foo1, f);
    //std::function<void(int, int)> func2 = std::bind(&Foo::foo4, f, std::placeholders::_1, std::placeholders::_2);
    //std::function<void(int, std::string)> func3 = std::bind(&Foo::foo3, f, std::placeholders::_1, std::placeholders::_2);
    handler.addHandler<void, int>(10, func, 10);
    handler.addHandler(5,func1);
    //handler.addHandler<void,int,int>(func2, 5, 6);
    //handler.addHandler<void,int,std::string>(func3, 10, std::string("Hello"));

    //std::function<int(int)> func4 = std::bind(&Foo::foo5, f, std::placeholders::_1);
    //handler.addHandler<int, int>(func4, 10);
    //handler.addHandler<void, int>(func, 10);
    //handler.addHandler<int, int>(func4, 10);
    //handler.addHandler<>(std::bind(&Foo::foo1, &f, std::placeholders::_1));

    //callFunc<Foo, void, void>(f, &Foo::foo1);
    return 0;
}
