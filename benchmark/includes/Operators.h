#ifndef __OPERATORS_H__
#define __OPERATORS_H__

#include <iostream>
#include <chrono>
#include <algorithm>
#include <random>
#include "Types.h"

using std::chrono::milliseconds;
using Clock = std::chrono::high_resolution_clock;

namespace {
template<class Container>
struct Empty {
    inline static Container make(std::size_t) {
        return Container();
    }
    inline static void clean() {}
};

template<class Container>
struct Filled {
    inline static Container make(std::size_t size)
    {
        return Container(size);
    }

    static const typename Container::value_type value;

    inline static void run(Container &c, std::size_t size) {
        for (size_t i = 0; i < size; ++i)
            c.push_back(value);
    }

    inline static void clean() {}
};

template<class Container>
struct FilledRandom {
    static std::vector<typename Container::value_type> v;
    inline static Container make(std::size_t size)
    {
        if (v.size() != size)
        {
            v.clear();
            v.reserve(size);
            for(std::size_t i = 0; i < size; ++i)
                v.push_back({i});
            std::shuffle(begin(v), end(v), std::mt19937());
        }
        Container c;
        for(std::size_t i = 0; i < size; ++i)
            c.push_back(v[i]);
        return c;
    }

    inline static void clean()
    {
        v.clear();
        v.shrink_to_fit();
    }
};

template<class Container>
std::vector<typename Container::value_type> FilledRandom<Container>::v;

template<class Container>
struct FillBackInserter {
    static const typename Container::value_type value;
    inline static void run(Container &c, std::size_t size) {
        std::fill_n(std::back_inserter(c), size, value);
    }
};

template<class Container> const typename Container::value_type FillBackInserter<Container>::value{};

template<class Container>
struct EmplaceBack {
    inline static void run(Container& c, std::size_t size) {
        for (size_t i = 0; i < size; ++i)
            c.emplace_back();
    }
};

template<class Container>
struct Reserve {
    inline static void run(Container& c, std::size_t size) {
        c.reserve(size);
    }
};

template<class Container>
struct FillFront {
    static const typename Container::value_type value;
    inline static void run(Container& c, std::size_t size) {
        std::fill_n(std::front_inserter(c), size, value);
    }
};

template<class Container> const typename Container::value_type FillFront<Container>::value{};

template<class T>
struct FillFront<std::vector<T>> {
    static const T value;
    inline static void run(std::vector<T> c, std::size_t size) {
        for(std::size_t i = 0; i < size; ++i) {
            c.insert(begin(c), value);
        }
    }
};

template<class T> const T FillFront<std::vector<T>>::value{};

template<class Container>
struct EmplaceFront {
    inline static void run(Container& c, std::size_t size) {
        for (size_t i = 0; i < size; ++i)
            c.emplace_front();
    }
};

template<class T>
struct EmplaceFront<std::vector<T>> {
    inline static void run(std::vector<T> &c, std::size_t size) {
        for (size_t i = 0; i < size; ++i)
            c.emplace(begin(c));
    }
};

template<class Container>
struct Find {
    static size_t X;
    inline static void run(Container& c, std::size_t size) {
        for(std::size_t i = 0; i < size; ++i)
        {
            if (std::find_if(std::begin(c), std::end(c), [&](decltype(*std::begin(c)) v){return v == i;}) == std::end(c))
                ++X;
        }
    }
};
template<class Container> size_t Find<Container>::X = 0;

template<class Container>
struct Sort {
    inline static void run(Container& c, std::size_t size) {
        std::sort(c.begin(), c.end());
    }
};

template<class T>
struct Sort<std::list<T>> {
    inline static void run(std::list<T> &c, std::size_t size) {
        c.sort();
    }
};

template<class Container>
struct Reverse {
    inline static void run(Container& c, std::size_t size) {
        std::reverse(c.begin(), c.end());
    }
};

template<class T>
struct Reverse<std::list<T>> {
    inline static void run(std::list<T> &c, std::size_t size) {
        c.reverse();
    }
};

template<class Container>
const typename Container::value_type Filled<Container>::value{};
template<class Container>
inline static void run(Container&, std::size_t) {
}

template<template<class> class Test, template<class> class... Rest, class Container>
inline static void run(Container& container, std::size_t size)
{
    Test<Container>::run(container, size);
    run<Rest...>(container, size);
}

template<typename Container,
    template<class> class CreateContainer,
    template<class> class ... TestContainer>
void bench(const std::string& type, std::size_t size)
{
    auto container = CreateContainer<Container>::make(size);
    Clock::time_point begin = Clock::now();
    run<TestContainer...>(container, size);
    Clock::time_point end = Clock::now();
    std::cout << "Duration(" << type << "): " << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()  << "ms\n";
    CreateContainer<Container>::clean();
}

}
#endif
