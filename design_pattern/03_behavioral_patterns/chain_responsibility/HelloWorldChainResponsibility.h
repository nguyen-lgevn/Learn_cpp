#ifndef __HELLOWORLD_CHAIN_RESPONSIBILITY_H__
#define __HELLOWORLD_CHAIN_RESPONSIBILITY_H__

#include "IHelloWorld.h"
#include <sstream>

namespace design_patterns {

class HelloWorldHandler: public IHelloWorld {
public:
    virtual void handle(std::stringstream&) = 0;

    virtual void setNext(std::shared_ptr<HelloWorldHandler> _next)
    {
        m_ptrNext = std::move(_next);
    }

    void sayHello() override {
        std::stringstream ss;
        handle(ss);
        if (m_ptrNext != nullptr)
        {
            m_ptrNext->handle(ss);
        }
        std::cout << ss.str() << std::endl;
    }

private:
    std::shared_ptr<HelloWorldHandler> m_ptrNext;
};

class HelloWorldFirstHandler: public HelloWorldHandler {
public:
    void handle(std::stringstream& ss) {
        ss << "Hello World ";
    }
};

class HelloWorldSecondHandler: public HelloWorldHandler {
public:
    void handle(std::stringstream& ss) {
        ss << "Chain of Responsibility";
    }
};

} // design_patterns

#endif
