#include <iostream>
#include <singleton/Singleton.h>
#include <visitor/IVisitor.h>
#include <visitor/IElement.h>

int main(int argc, char* argv[])
{
    std::cout << "==============================================" << std::endl;
    std::cout << "==========  Design patterns ==================" << std::endl;
    std::cout << "==============================================" << std::endl;

    std::cout << "===========     Singleton   ==================" << std::endl;
    design_pattern::singleton::HelloWorldSingleton::getInstance().sayHello();

    std::cout << "===========     Visitor     ==================" << std::endl;
    design_pattern::visitor::ElementEnglish *e = new design_pattern::visitor::ElementEnglish(); 
    design_pattern::visitor::ElementFrench *f = new design_pattern::visitor::ElementFrench();

    design_pattern::visitor::Visitor v;
    e->accept(v);
    f->accept(v);
    return 0;
}
