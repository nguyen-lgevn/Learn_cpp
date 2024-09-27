#include <iostream>
#include <vector>
#include <memory>

class Foo {
    public:
        Foo(int _value) {value = _value;}
        ~Foo() {std::cout << "~Foo()" << std::endl;}
        void toString() {std::cout << value << std::endl;}
    private:
    int value;
};

int main(int argc, char* argv[])
{
    std::vector<std::shared_ptr<Foo>> arr;
    std::shared_ptr<Foo> foo = std::make_shared<Foo>(10);
    arr.push_back(foo);
    std::shared_ptr<Foo> f = arr.front();

    if (f != nullptr)
    {
        std::cout << "not nullptr(f): " << f.get() << std::endl;
    }
    std::cout << "Erase element begin 1: "  << std::endl;
    arr.erase(arr.begin());
    std::cout << "Erase element end 1!"  << std::endl;
    f->toString();
    std::cout << "arr len: " << arr.size() << std::endl;

    std::shared_ptr<Foo> g = arr.front();
    if (g != nullptr)
    {
        std::cout << "not nullptr(g): " << g.get() << std::endl;
    }
    std::cout << "Erase element begin 2: "  << std::endl;
    arr.erase(arr.begin());
    std::cout << "Erase element end 2!"  << std::endl;
    g->toString();
    std::cout << "arr len: " << arr.size() << std::endl;
    return 0;
}
