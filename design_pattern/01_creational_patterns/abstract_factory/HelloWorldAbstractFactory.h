#ifndef __HELLOWORLD_ABSTRACTFACTORY_H__
#define __HELLOWORLD_ABSTRACTFACTORY_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldAbstractFactoryObject: public IHelloWorld {
public:
    void sayHello() {
        std::cout << "Hello World Abstract Factory\n";
    }
};

class HelloWorldAbstractFactory {
public:
    std::unique_ptr<HelloWorldAbstractFactoryObject> createInstance() {
        return std::make_unique<HelloWorldAbstractFactoryObject>();
    }
};

} // design_patterns

#endif
