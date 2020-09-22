#ifndef __HELLOWORLD_ADAPTER_H__
#define __HELLOWORLD_ADAPTER_H__

#include "IHelloWorld.h"
#include <functional>

namespace design_patterns {

template<class T>
class HelloWorldAdapter: public IHelloWorld {
public:
    HelloWorldAdapter(T* t, void(T::*m)())
    {
        m_object = std::unique_ptr<T>(t);
        m_function = std::bind(m, t);
    }

    void sayHello() override {
        m_function();
    }

private:
    std::unique_ptr<T>  m_object;
    std::function<void()> m_function;
};

class HelloWorldDesignPatternAdapter {
public:

    void sayHelloWorldDesignPatternAdapter() {
        std::cout << "Hello World Adapter\n";
    }
};

} // design_patterns

#endif
