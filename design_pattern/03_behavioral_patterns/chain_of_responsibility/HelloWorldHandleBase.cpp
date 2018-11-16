#include "HelloWorldHandleBase.h"
#include <iostream>
#include <sstream>

using namespace design_patterns;
using namespace chain_of_responsibility;

HelloWorldHandleBase::HelloWorldHandleBase()
{
    m_next = NULL;
}

void HelloWorldHandleBase::handle(std::string& str)
{
    if (m_next != NULL)
        m_next->handle(str);
}

void HelloWorldHandleBase::setNext(HelloWorldHandleBase* next)
{
    m_next = next;
}

void HelloWorldHandleBase::sayHello()
{
    std::string str;
    handle(str);
    std::cout << str << std::endl;
}
