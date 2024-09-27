#include <iostream>

template<class Tag>
struct stowed {
    static typename Tag::type value;
};
template<class Tag>
typename Tag::type stowed<Tag>::value;


template<class Tag, typename Tag::type x>
struct stowed_private {
    stowed_private() {stowed<Tag>::value = x;};
    static stowed_private instance;
};
template<class Tag, typename Tag::type x>
stowed_private<Tag,x> stowed_private<Tag,x>::instance;

struct Foo {

    public:
        Foo(int _a) {
            a = _a;
            b = 10;
            std::cout << "Foo: " << (void*)this << "\t a: " << (void*)&a
                << "\t b: " << (void*)&b
                << "\t rel: " << (char*)&a - (char*)this
                << "\t func ptr: " << &Foo::foo << std::endl;
        }



    private:
        int a;
        int b;
        void foo() {std::cout << __FUNCTION__ << " is private" << std::endl;}
};

struct Foo_x {typedef int (Foo::*type);};

template class stowed_private<Foo_x, &Foo::b>;

struct Foo_foo {typedef void (Foo::*type)();};

template class stowed_private<Foo_foo, &Foo::foo>;

int main(int argc, char **argv)
{
    Foo foo(2);
    std::cout << (void*)&foo << std::endl;
    std::cout << foo.*stowed<Foo_x>::value << std::endl;
    (foo.*stowed<Foo_foo>::value)();
    return 0;
}
