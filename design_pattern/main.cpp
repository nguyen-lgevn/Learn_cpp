#include <iostream>
#include <singleton/Singleton.h>

int main(int argc, char* argv[])
{
    std::cout << "==============================================" << std::endl;
    std::cout << "==========  Design patterns ==================" << std::endl;
    std::cout << "==============================================" << std::endl;

    std::cout << "===========     Singleton   ==================" << std::endl;
    design_pattern::singleton::HelloWorldSingleton::getInstance().sayHello();
    return 0;
}
