#ifndef __HELLOWORLD_FACTORYMETHOD_H__
#define __HELLOWORLD_FACTORYMETHOD_H__

#include "IHelloWorld.h"
#include <iostream>
#include <memory>

namespace design_patterns {

class HelloWorldFactoryMethod: public IHelloWorld {
public:
    void sayHello() override {
        std::cout << "Hello World Factory Method\n";
    }
};

class FactoryHelloWorld {
public:
    std::unique_ptr<IHelloWorld> createHelloWorld() {
        return std::make_unique<HelloWorldFactoryMethod>();
    }
};

} // design_patterns

#endif
