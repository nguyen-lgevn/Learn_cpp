#ifndef __HELLOWORLD_TEMPLATEMETHOD_H__
#define __HELLOWORLD_TEMPLATEMETHOD_H__

#include "IHelloWorld.h"

namespace design_patterns {

class IHelloWorldTemplateMethod: public IHelloWorld {
public:
    void sayHello() override  {
        std::cout << hello() << method() << std::endl;
    }

    virtual std::string hello() = 0;
    virtual std::string method() = 0;
};

class HelloWorldTemplateMethod: public IHelloWorldTemplateMethod {
public:
    std::string hello() {
        return "Hello World ";
    }

    std::string method() {
        return "Template Method";
    }
};

} // design_patterns

#endif
