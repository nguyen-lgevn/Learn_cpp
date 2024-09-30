// Question: 
// Source:  
//

#include <chrono>
#include <thread>
#include <future>
#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <cassert>

extern void do_something()
{
}

typedef long long unsigned int call_p_sec_t;
typedef ::std::function<void()> the_call_t;

template <typename T>
call_p_sec_t calls_per_second (const T &thecall, unsigned int interval)
{
    auto now = [] () -> decltype(::std::chrono::high_resolution_clock::now()) {
        return ::std::chrono::high_resolution_clock::now();
    };

    typedef ::std::chrono::duration<long double> timediff_t;
    unsigned long long count = 0;
    const auto start = now();

    long double currtime_as_ldbl = (timediff_t(now() - start)).count();
    while (currtime_as_ldbl < interval) {
        thecall();
        ++count;
        currtime_as_ldbl = (timediff_t(now() - start)).count();
    }
    return count / interval;
}

static bool end_thread_flag = false;

void end_thread()
{
    end_thread_flag = true;
}

//void worker_thread()
//{
//    while (!end_thread_flag) {
//        the_call_t a_call;

//    }
//}

int main(int argc, const char* const argv[])
{
    using ::std::cout;
    using ::std::endl;
    using ::std::async;
    using ::std::thread;
    using ::std::launch;
    using ::std::setw;

    assert(argc == 2);

    int whichtests = 31;
    if (argc > 1) {
        whichtests = ::std::stoi(argv[1]);
    }
    if (whichtests & 0x1) {
        cout << "Do nothing calls per second:" << setw(10) << calls_per_second([](){}, 5) << endl;
    }
    if (whichtests & 0x2) {
        cout << "Empty calls per second:" << setw(10) << calls_per_second([](){do_something();}, 5) << endl;
    }
    if (whichtests & 0x4) {
        cout << "New thead calls per second:" << setw(10) << calls_per_second([](){
                thread t{do_something};
                t.join();
                },5) << endl;
    }
}
