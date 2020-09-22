#ifndef __HELLOWORLD_PROXY_H__
#define __HELLOWORLD_PROXY_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldProxyDefault: public IHelloWorld {
public:
    void sayHello() override {
        std::cout << "Hello World Proxy\n";
    }
};

class HelloWorldProxy: public IHelloWorld {
public:
    HelloWorldProxy() {
        m_ptr = std::make_shared<HelloWorldProxyDefault>();
    }

    void sayHello() override {
        m_ptr->sayHello();
    }

private:
    std::shared_ptr<HelloWorldProxyDefault> m_ptr;
};

} // design_patterns

#endif
