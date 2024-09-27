#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>

class Foo {
public:
    static std::shared_ptr<Foo> getInstance() {
        static std::shared_ptr<Foo> instance(new Foo);
        return instance;
    }

    ~Foo() {
        std::cout << "Foo destructor" << std::endl;
    }
};

void foo() {

    const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    const std::time_t tc = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::cout << std::put_time(std::localtime(&tc), "%F %T.\t" ) << __FUNCTION__ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    {
        std::shared_ptr<Foo> f = Foo::getInstance();
    }
}


void bar() {
    const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    const std::time_t tc = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::cout << std::put_time(std::localtime(&tc), "%F %T.\t" ) << __FUNCTION__ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    exit(0);
}

int main(int argc, char **argv)
{
    std::thread t(foo);
    std::thread u(bar);
    t.join();
    u.join();
    while (1)
    {
        const std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        const std::time_t tc = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
        std::cout << std::put_time(std::localtime(&tc), "%F %T.\n" ) << std::flush;
    }
    return 0;
}
