#ifndef __HELLO_WORLD_FIRST_HANDLE_H_
#define __HELLO_WORLD_FIRST_HANDLE_H_

#include "HelloWorldHandleBase.h"

namespace design_patterns {
namespace chain_of_responsibility {

class HelloWorldFirstHandle: public HelloWorldHandleBase
{
    void handle(std::string& str)
    {
        std::stringstream ss(str);
        ss << "Hello ";
        str += ss.str();
        HelloWorldHandleBase::handle(str);
    }
};

class HelloWorldSecondHandle: public HelloWorldHandleBase
{
    void handle(std::string& str)
    {
        std::stringstream ss(str);
        ss << "World ";
        str += ss.str();
        HelloWorldHandleBase::handle(str);
    }
};

class HelloWorldThirdHandle: public HelloWorldHandleBase
{
    void handle(std::string& str)
    {
        std::stringstream ss(str);
        ss << "Chain of Responsibility";
        str += ss.str();
        HelloWorldHandleBase::handle(str);
    }
};

} // chain_of_responsibility
} // design_patterns

#endif
