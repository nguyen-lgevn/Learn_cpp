#ifndef __HELLOWORLD_INTERPRETER_H__
#define __HELLOWORLD_INTERPRETER_H__

#include "IHelloWorld.h"
#include <map>

namespace design_patterns {

class HelloWorldInterpreter: public IHelloWorld {
    using Func = void (HelloWorldInterpreter::*)(void);
public:
    HelloWorldInterpreter() {
        m_mapFunc["sayHello"] = &HelloWorldInterpreter::sayHello;
    }

    void sayHello() override {
        std::cout << "Hello World Interpreter\n";
    }

    void interpreter(std::string function) {
        if (m_mapFunc.count(function))
        {
            (this->*m_mapFunc[function])();
        }
        else
        {
            std::cout << "Cannot find function\n";
        }
    }

private:
    std::map<std::string, Func> m_mapFunc;
};

} // design_patterns

#endif
