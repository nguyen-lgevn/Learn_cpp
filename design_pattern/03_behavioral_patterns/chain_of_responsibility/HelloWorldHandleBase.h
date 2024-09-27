#ifndef __HELLO_WORLD_HANDLE_BASE_H__
#define __HELLO_WORLD_HANDLE_BASE_H__

#include "IHelloWorld.h"
#include <iostream>
#include <sstream>
#include <string>

namespace design_patterns {
namespace chain_of_responsibility {

class HelloWorldHandleBase: public IHelloWorld {
public:
    HelloWorldHandleBase();

    virtual void handle(std::string& ss);
    void setNext(HelloWorldHandleBase* next);

    void sayHello() override;
    
private:
    HelloWorldHandleBase* m_next;
};

} // chain_of_responsibility
} // design_patterns

#endif
