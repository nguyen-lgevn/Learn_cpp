#ifndef __HELLOWORLD_PROTOTYPE_H__
#define __HELLOWORLD_PROTOTYPE_H__

#include "IHelloWorld.h"
#include <memory>

namespace design_patterns {

class HelloWorldPrototype: public IHelloWorld {
public:
    std::unique_ptr<HelloWorldPrototype> clone() {
        return std::make_unique<HelloWorldPrototype>(*this);
    }

    void sayHello() override {
        std::cout << "Hello World Prototype\n";
    }

    static std::unique_ptr<HelloWorldPrototype> PROTOTYPE;
};

std::unique_ptr<HelloWorldPrototype> HelloWorldPrototype::PROTOTYPE = std::make_unique<HelloWorldPrototype>();

} // design_patterns

#endif
