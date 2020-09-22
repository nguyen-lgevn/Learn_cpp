#ifndef __HELLOWORLD_BUILDER_H__
#define __HELLOWORLD_BUILDER_H__

#include "IHelloWorld.h"
#include <string>

namespace design_patterns {

class HelloWorldBuilder: public IHelloWorld {
public:
    HelloWorldBuilder() {
        strHelloWorldBuilder = "Hello World ";
    }

    void construct(std::string word) {
        strHelloWorldBuilder += word;
    }

    void sayHello() override {
        std::cout << strHelloWorldBuilder << std::endl;
    }

private:
    std::string strHelloWorldBuilder;
};

} // design_patterns
#endif
