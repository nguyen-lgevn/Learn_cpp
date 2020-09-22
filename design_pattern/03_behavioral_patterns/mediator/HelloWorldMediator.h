#ifndef __HELLOWORLD_MEDIATOR_H__
#define __HELLOWORLD_MEDIATOR_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldMediator;

class HelloWorldMediatorObject: public IHelloWorld, public std::enable_shared_from_this<HelloWorldMediatorObject> {
public:
    void sayHello() = 0;

    void setMediator(std::shared_ptr<HelloWorldMediator> _ptrMediator)
    {
        m_ptrMediator = std::move(_ptrMediator);
    }

    void handle();

private:
    std::shared_ptr<HelloWorldMediator> m_ptrMediator;
};

class HelloWorldFirstObject: public HelloWorldMediatorObject {
public:
    void sayHello() override {
        std::cout << "Hello World ";
    }
};

class HelloWorldSecondObject: public HelloWorldMediatorObject {
public:
    void sayHello() override {
        std::cout << "Mediator\n";
    }
};

class HelloWorldMediator {
public:
    HelloWorldMediator(std::shared_ptr<HelloWorldFirstObject> _ptrFirst,
            std::shared_ptr<HelloWorldSecondObject> _ptrSecond)
    {
        m_ptrFirstObj = std::move(_ptrFirst);
        m_ptrSecondObj = std::move(_ptrSecond);
    }

    void handleEvent() {
        m_ptrFirstObj->handle();
        m_ptrSecondObj->handle();
    }

    void handleObj(std::shared_ptr<HelloWorldMediatorObject> _ptr) {
        _ptr->sayHello();
    }

private:
    std::shared_ptr<HelloWorldFirstObject> m_ptrFirstObj;
    std::shared_ptr<HelloWorldSecondObject> m_ptrSecondObj;
};

void HelloWorldMediatorObject::handle() {
    m_ptrMediator->handleObj(shared_from_this());
}

} // design_patterns

#endif
