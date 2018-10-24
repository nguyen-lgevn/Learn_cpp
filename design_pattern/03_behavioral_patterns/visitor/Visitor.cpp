#include "IVisitor.h"

using namespace design_pattern;
using namespace visitor;

void Visitor::visit(ElementEnglish *element)
{
    element->sayHello();
}
    

void Visitor::visit(ElementFrench *element)
{
    element->sayHello();
}
