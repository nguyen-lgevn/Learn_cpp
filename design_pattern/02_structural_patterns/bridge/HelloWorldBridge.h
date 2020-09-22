#ifndef __HELLOWORLD_BRIDGE_H__
#define __HELLOWORLD_BRIDGE_H__

#include "IHelloWorld.h"

namespace design_patterns {

class IHelloWorldImpl {
public:
    virtual void helloWorld() = 0;
};

class IHelloWorldBridgeImpl: public IHelloWorldImpl {
public:
    void helloWorld() override {
        std::cout << "Hello World Bridge\n";
    }
};

class HelloWorldBridge: public IHelloWorld {
public:
    HelloWorldBridge() {
        m_pHelloWorldBridge = std::make_unique<IHelloWorldBridgeImpl>();
    }

    void sayHello() override {
        m_pHelloWorldBridge->helloWorld();
    }

private:
    std::unique_ptr<IHelloWorldImpl> m_pHelloWorldBridge;
};

} // design_patterns

#endif
