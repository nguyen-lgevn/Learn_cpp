#ifndef __HELLOWORLD_STRATEGY_H__
#define __HELLOWORLD_STRATEGY_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldStrategy: public IHelloWorld {
public:
    void sayHello() override {
        std::cout << "Hello World Strategy\n";
    }
};

class HelloWorldStrategyContext {
public:
    void setStrategy(std::shared_ptr<HelloWorldStrategy> _ptr) {
        m_ptrStrategy = std::move(_ptr);
    }

    void sayHello() {
        m_ptrStrategy->sayHello();
    }

private:
    std::shared_ptr<HelloWorldStrategy> m_ptrStrategy;
};

} // design_patterns

#endif
