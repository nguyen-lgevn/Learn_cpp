#include "IElement.h"
#include "IVisitor.h"

void IElementEnglish::accept(Visitor &v)
{
    v.visit(this);
}

void IElementEnglish::sayHello()
{
    this->sayHelloEnglish();
}

void IElementEnglish::sayHelloEnglish()
{
    std::cout << "Hello World" << std::endl;
}

void IElementFrench::visit(Visitor &v)
{
    v.visit(this);
}

void IElementFrench::sayHello()
{
    this->sayHelloFrench();
}

void IElementFrench::sayHelloFrench()
{
    std::cout << "Bonjour" << std::endl;
}
