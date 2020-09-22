#ifndef __HELLOWORLD_VISITOR_H__
#define __HELLOWORLD_VISITOR_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldElement {
public:
    virtual void accept(std::shared_ptr<class HelloWorldVisitor> _ptr) = 0;
};

class HelloWorldElementHello: public HelloWorldElement, public IHelloWorld,
    public std::enable_shared_from_this<HelloWorldElementHello> {
public:
    void accept(std::shared_ptr<class HelloWorldVisitor> _ptr) override;

    void sayHello() override {
        std::cout << "Hello World ";
    }
};

class HelloWorldElementVisitor: public HelloWorldElement, public IHelloWorld,
    public std::enable_shared_from_this<HelloWorldElementVisitor> {
public:
    void accept(std::shared_ptr<HelloWorldVisitor> _ptr) override;

    void sayHello() override {
        std::cout << "Visitor\n";
    }
};

class HelloWorldVisitor {
public:
    void visit(std::shared_ptr<HelloWorldElementHello> _ptr) {
        _ptr->sayHello();
    }

    void visit(std::shared_ptr<HelloWorldElementVisitor> _ptr) {
        _ptr->sayHello();
    }
};

void HelloWorldElementHello::accept(std::shared_ptr<HelloWorldVisitor> _ptr) {
    _ptr->visit(shared_from_this());
}

void HelloWorldElementVisitor::accept(std::shared_ptr<HelloWorldVisitor> _ptr) {
    _ptr->visit(shared_from_this());
}

} // design_patterns

#endif
