#ifndef __HELLOWORLD_DECORATOR_H__
#define __HELLOWORLD_DECORATOR_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldDecorator: public IHelloWorld {
public:
    void sayHello() override {
        std::cout << "Hello World Decorator\n";
    }
};

class DecoratorHelloWorld: public IHelloWorld {
public:
    DecoratorHelloWorld(std::shared_ptr<IHelloWorld> _ptr)
    {
        m_ptrHelloWorld = _ptr;
    }

    void sayHello() override {
        m_ptrHelloWorld->sayHello();
    }

private:
    std::shared_ptr<IHelloWorld> m_ptrHelloWorld;
};

} // design_patterns

#endif
