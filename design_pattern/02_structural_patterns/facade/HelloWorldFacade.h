#ifndef __HELLOWORLD_FACADE_H_
#define __HELLOWORLD_FACADE_H_

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldFacadeHello {
public:
    std::string getHelloWorld() {
        return "Hello ";
    }
};

class HelloWorldFacadeWorld {
public:
    std::string getHelloWorld() {
        return "World ";
    }
};

class HelloWorldFacade: public IHelloWorld {
public:
    HelloWorldFacade(int _state = 0): m_state(_state) {
        m_pHelloWorldFacadeHello = std::make_shared<HelloWorldFacadeHello>();
        m_pHelloWorldFacadeWorld = std::make_shared<HelloWorldFacadeWorld>();
    }

    void sayHello() override {
        std::cout << m_pHelloWorldFacadeHello->getHelloWorld()
                  << m_pHelloWorldFacadeWorld->getHelloWorld()
                  << "Facade\n";
    }
private:
    int m_state;
    std::shared_ptr<HelloWorldFacadeHello> m_pHelloWorldFacadeHello;
    std::shared_ptr<HelloWorldFacadeWorld> m_pHelloWorldFacadeWorld;
};



}

#endif
