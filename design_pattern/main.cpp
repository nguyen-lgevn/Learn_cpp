#include <iostream>
// Creator patterns 
#include <singleton/Singleton.h>

// Structural patterns
#include <adapter/HelloWorldAdapter.h>

// Behavioral patterns
#include <visitor/IVisitor.h>
#include <visitor/IElement.h>

#include <chain_of_responsibility/HelloWorldFirstHandle.h>

int main(int argc, char* argv[])
{
    std::cout << "============================================================" << std::endl;
    std::cout << "========================  Design patterns ==================" << std::endl;
    std::cout << "============================================================" << std::endl;

    std::cout << "=========================     Singleton   ==================" << std::endl;
    design_pattern::singleton::HelloWorldSingleton::getInstance().sayHello();

    std::cout << "=========================     Adapter     ==================" << std::endl;
    design_pattern::structural::HelloWorldDesignPattern helloWorldDesignPattern;
    design_pattern::structural::HelloWorldAdapter helloWorldAdapter(&helloWorldDesignPattern);
    helloWorldAdapter.sayHelloAdapter();

    std::cout << "=========================     Visitor     ==================" << std::endl;
    design_pattern::visitor::ElementEnglish *e = new design_pattern::visitor::ElementEnglish(); 
    design_pattern::visitor::ElementFrench *f = new design_pattern::visitor::ElementFrench();

    design_pattern::visitor::Visitor v;
    e->accept(v);
    f->accept(v);

    std::cout << std::endl;
    std::cout << "===============     Chain of responsibility    ==============" << std::endl;
    design_patterns::chain_of_responsibility::HelloWorldFirstHandle root;
    design_patterns::chain_of_responsibility::HelloWorldSecondHandle two;
    design_patterns::chain_of_responsibility::HelloWorldThirdHandle three;
    
    root.setNext(&two);
    two.setNext(&three);

    root.sayHello();

    return 0;
}
