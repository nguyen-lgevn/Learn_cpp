#include <stdio.h>
#include <stdarg.h>
#include <iostream>
void test_log(char* str, const char* fmt, ...);


template<class... Args>
void print(Args... args)
{
    (std::cout << ... << args) << "\n";
}

#include <type_traits>

template<class Head, class... Tail>
using are_same = std::conjunction<std::is_same<Head, Tail>...>;

template<class Head, class... Tail, class = std::enable_if_t<are_same<Head, Tail...>::value, void>>
void print_same_type(Head head, Tail... tail)
{
    std::cout << head;
    (std::cout << ... << tail) << "\n";
}

int main()
{
    char str[256];
    test_log(str, "%s", "test");
    test_log(str, "%s %s %d", "str1" , "str2" ,1);
    test_log(str, "%f", 0.2);
    return 0;
}
void test_log(char* str, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vsprintf(str, fmt, args);
    va_end(args);
    printf("Test log: %s\n", str);
}
