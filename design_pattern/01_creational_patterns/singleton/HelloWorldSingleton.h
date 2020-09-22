#ifndef __HELLOWORLD_SINGLETON_H__
#define __HELLOWORLD_SINGLETON_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldSingleton: public IHelloWorld {
public:
    static HelloWorldSingleton& getInstance() {
        static HelloWorldSingleton instance;
        return instance;
    }

    void sayHello() override {
        std::cout << "Hello World Singleton\n";
    }

private:
    HelloWorldSingleton() {}

    HelloWorldSingleton(const HelloWorldSingleton&) = delete;
    HelloWorldSingleton(HelloWorldSingleton&&) = delete;
    HelloWorldSingleton& operator=(const HelloWorldSingleton&) = delete;
    HelloWorldSingleton& operator=(HelloWorldSingleton&&) = delete;
};

} // design_patterns

#endif
