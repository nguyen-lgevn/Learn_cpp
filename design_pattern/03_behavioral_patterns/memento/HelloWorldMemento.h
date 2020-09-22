#ifndef __HELLOWORLD_MEMENTO_H__
#define __HELLOWORLD_MEMENTO_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldMemento {
public:
    HelloWorldMemento(std::string _state): m_state(_state) {}

    std::string getSavedState() {
        return m_state;
    }

private:
    std::string m_state;
};

class HelloWorldMementoOriginator: public IHelloWorld {
public:
    std::shared_ptr<HelloWorldMemento> createMemento() {
        return std::make_shared<HelloWorldMemento>(m_strHelloWorld);
    }

    void restoreFromMemento(std::shared_ptr<HelloWorldMemento> _ptr) {
        m_strHelloWorld = _ptr->getSavedState();
    }

    void sayHello() override {
        std::cout << m_strHelloWorld << std::endl;
    }

    void setState(std::string _state) {
        m_strHelloWorld = _state;
    }

private:
    std::string m_strHelloWorld;
};

} // design_patterns

#endif
