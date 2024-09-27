#ifndef __TYPES_H__
#define __TYPES_H__

#include <array>
#include <vector>
#include <list>
#include <forward_list>
#include <deque>
#include <map>
#include <string>
#include <tuple>
#include <queue>
#include <stack>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <typeinfo>
#include <type_traits>

namespace {

template<typename T>
constexpr bool is_trivial_size(std::size_t size) {
    return std::is_trivial<T>::value && sizeof(T) == size;
}

template<typename T>
constexpr bool is_non_trivial_size(std::size_t size) {
    return !std::is_trivial<T>::value && sizeof(T) == size
        && std::is_copy_constructible<T>::value
        && std::is_copy_assignable<T>::value
        && std::is_move_assignable<T>::value;
}

template<typename T>
constexpr bool is_non_trivial_nothrow_movable() {
    return !std::is_trivial<T>::value
        && std::is_nothrow_move_constructible<T>::value
        && std::is_nothrow_move_assignable<T>::value;
}

template<typename T>
constexpr bool is_non_trivial_non_nothrow_movable() {
    return !std::is_trivial<T>::value
        && std::is_move_constructible<T>::value
        && std::is_move_assignable<T>::value
        && !std::is_nothrow_move_constructible<T>::value
        && !std::is_nothrow_move_assignable<T>::value;
}
template<typename T>
constexpr bool is_non_trivial_non_movable() {
    return !std::is_trivial<T>::value
        && std::is_copy_constructible<T>::value
        && std::is_copy_assignable<T>::value
        && !std::is_move_constructible<T>::value
        && !std::is_move_assignable<T>::value;
}

template<int N>
struct Trivial {
    std::size_t a;
    std::array<unsigned char, N - sizeof(a)> b;
};

template<>
struct Trivial<sizeof(std::size_t)> {
    std::size_t a;
};

template<typename T>
struct has_const_iterator {
private:
    using yes = char;
    using no = yes[2];
    template<typename C> static yes &test(typename C::const_iterator*);
    template<typename C> static no &test(...);
public:
    static const bool value = sizeof(test<T>(nullptr)) == sizeof(yes);
    typedef T type;
};

/*
template<typename T>
struct is_containter {
    static const bool value = false;
};

template<typename T, typename Alloc>
struct is_container<std::vector<T, Alloc> > {
    static const bool value = true;
};
*/

// Source: stackoverflow.com/questions/9407367/determine-if-a-type-is-an-stl-container-at-compile-time

namespace is_stl_container_impl {
    template<typename T> struct is_stl_container:std::false_type{};
    template<typename T, std::size_t N> struct is_stl_container<std::array<T, N>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::vector<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::list<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::deque<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::forward_list<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::set<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::multiset<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::map<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::multimap<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::unordered_set<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::unordered_map<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::stack<Args...>>:std::true_type{};
    template<typename... Args> struct is_stl_container<std::queue<Args...>>:std::true_type{};
} // is_stl_container_impl end

template<typename T> struct is_stl_container {
    static constexpr bool const value = is_stl_container_impl::is_stl_container<std::decay_t<T>>::value;
};

}
#endif
