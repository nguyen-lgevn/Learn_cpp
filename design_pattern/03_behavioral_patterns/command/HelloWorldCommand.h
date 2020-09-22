#ifndef __HELLOWORLD_COMMAND_H__
#define __HELLOWORLD_COMMAND_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldCommandObject: public IHelloWorld {
public:
    void sayHello() override {
        std::cout << "Hello World Command\n";
    }

};

class HelloWorldCommand {
    using Action = void (HelloWorldCommandObject::*)(void);
public:
    HelloWorldCommand(std::shared_ptr<HelloWorldCommandObject> _ptr)
    {
        m_ptrHelloWorldCommandObj = std::move(_ptr);
        action = &HelloWorldCommandObject::sayHello;
    }

    void execute() {
        (m_ptrHelloWorldCommandObj.get()->*action)();
    }
private:
    std::shared_ptr<HelloWorldCommandObject> m_ptrHelloWorldCommandObj;
    Action action;
};

} // design_patterns

#endif
