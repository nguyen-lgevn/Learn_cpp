#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstring>

struct Foo {
    int a;
    int b;
    std::string str;
};

char* m_buff;


void write_data(const void* _data, int _size)
{
    memcpy(m_buff, (const char*)_data, _size);
}

void read_data()
{
    Foo* ptr = (Foo*)m_buff;
    std::cout << ptr->a << " " << ptr->b << " " << ptr->str << std::endl;
}

int main(int argc, char **argv)
{
    std::cout << "size of int: " << sizeof(int) << std::endl;
    std::cout << "size of string: " << sizeof(std::string) << std::endl;
    Foo foo;
    foo.a = 10;
    foo.b = 20;
    foo.str = "This is a loooooooooooooooong string";
    std::cout << sizeof(Foo) << std::endl;
    std::cout << foo.a << " " << foo.b << " " << foo.str << std::endl;

    m_buff = (char*)malloc(2048);
    memset(m_buff, 0, 2048);
    write_data((const void*)&foo, (int)sizeof(foo));

    read_data();

    return 0;
}
