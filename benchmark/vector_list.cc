#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <type_traits>
#include <memory>

using Clock = std::chrono::high_resolution_clock;
static const std::size_t REPEAT = 10;

void print_current_time(std::string msg)
{
    auto time = Clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(time);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    std::cout << ss.str() << ": " << msg << std::endl;
}

/*
template<typename T>
struct has_const_iterator
{
private:
    template<typename C> static char test(typename C::const_iterator*);
    template<typename C> static int test(...);
public:
    enum {value = sizeof(test<T>(0)) == sizeof(char)};
};
*/

template <template<typename, typename> class Container, typename Value,
    typename Allocator=std::allocator<Value> >
void bench_push_back(Container<Value, Allocator>& c, int size)
{
    //static const typename Container::value_type value;
    for(std::size_t i = 0; i < size; ++i)
    {
        c.push_back(i);
    }
    std::cout << "Size:" << c.size() << std::endl;
    c.clear();
}

template <template<typename, typename> class Container, typename Value,
    typename Allocator=std::allocator<Value> >
void bench_emplace_back(Container<Value, Allocator>& c, int size)
{
    //static const typename Container::value_type value;
    for(std::size_t i = 0; i < size; ++i)
    {
        c.push_back(i);
    }
    std::cout << "Size:" << c.size() << std::endl;
}

int main(int argc, char* argv[])
{
    print_current_time("start");
    auto begin = Clock::now();
    std::vector<int> vec;
    bench_push_back<std::vector>(vec, 10000);
    auto end = Clock::now();
    std::chrono::duration<double, std::milli> ms = end - begin;
    std::cout << "Duration: " << ms.count() << " ms\n";

    begin = Clock::now();
    std::list<int> lst;
    bench_push_back<std::list>(lst, 10000);
    end = Clock::now();
    ms = end - begin;
    std::cout << "Duration: " << ms.count() << " ms\n";
    print_current_time("end");
    return 0;
}
