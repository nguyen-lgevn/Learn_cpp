//#include "Timer.h"
#include <iostream>
#include <functional>
#include <type_traits>
#include <cstdio>

//#include "CallbackTimer.h"

#include "Timer1.h"

class Foo {
    public:
        void test()
        {
            std::cout << "Foo::test" << std::endl;
        }

        int test_foo(int a)
        {
            return a*2;
        }
};

void foo()
{
    std::cout << "I am foo\n";
}

template<>
class Timer<void>
{

};

char f() {
    return '.';
}

int main(int argc, char* argv[])
{
    
    //Foo f;
    //Utils::Timer::later(2000, false, &Foo::test);
/*
    static bool b = false;
    static int i = 0;

    std::thread t([](){
            std::cout << "new thread" << std::endl;
            while (1)
            {
                i++;
                if (b == true)
                    break;
            }
            });
    t.detach();
    */
    //Utils::Timer timer;

    //timer.setTimer(3000, true, f, &Foo::test);
    //timer.setTimer(3000, true, f, &Foo::test_foo, 5);
        
    //timer.later(3000, false, [](){
    //        std::cout << "lambda func " << i << std::endl;
    //        b = true;
    //        });
    
    //timer.run();
    
   /* 
    Foo f;
    
    auto l = std::bind(&Foo::test, f);
    l();

    auto k = std::bind(&Foo::test_foo, &f, std::placeholders::_1);
    std::cout << k(5) << std::endl; 

    std::result_of<decltype(&Foo::test_foo)(Foo,int)>::type g;
    static_assert(std::is_same<decltype(g), int>::value, "Test");
    
    std::function<typename std::result_of<decltype(&Foo::test_foo)(Foo)>::type()> func;// = std::bind(std::forward<Foo>(&Foo::test_foo), f);
    func();
    */
    /*
    Timer::CallbackTimer cbtimer;
    cbtimer.start(5, foo);
    */
    using std::chrono::milliseconds;
    Timer<char> timer(f);
    timer.start(milliseconds(10));
    for (unsigned i = 0; i <= 10; ++i)
    {
        std::this_thread::sleep_for(milliseconds(100));
        if (i == 10) timer.stop();
        auto results = timer.results();
        for (const auto& r: results)
            std::cout << r;
        std::cout << "\n";
    }
    return 0;
}
