#include <iostream>
#include "singleton/Singleton.h"

using namespace design_pattern; 
using namespace singleton;

HelloWorldSingleton::HelloWorldSingleton()
{

}

HelloWorldSingleton& HelloWorldSingleton::getInstance()
{
    static HelloWorldSingleton instance;
    return instance;
}

void HelloWorldSingleton::sayHello()
{
    std::cout << "HelloWorldSingleton::sayHello()" << std::endl;
}

