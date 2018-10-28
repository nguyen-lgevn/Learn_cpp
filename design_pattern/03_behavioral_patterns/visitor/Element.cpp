#include "IElement.h"
#include "IVisitor.h"

using namespace design_pattern;
using namespace visitor;

void ElementEnglish::accept(Visitor &v)
{
    v.visit(this);
}

void ElementEnglish::sayHello()
{
    this->sayHelloEnglish();
}

void ElementEnglish::sayHelloEnglish()
{
    std::cout << "Hello World" << std::endl;
}

void ElementFrench::accept(Visitor &v)
{
    v.visit(this);
}

void ElementFrench::sayHello()
{
    this->sayHelloFrench();
}

void ElementFrench::sayHelloFrench()
{
    std::cout << "Bonjour" << std::endl;
}
