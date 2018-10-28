#ifndef __IELEMENT_H__
#define __IELEMENT_H__

#include <iostream>

namespace design_pattern {

namespace visitor {

class IElement {
public:
    virtual void accept(class Visitor &v) = 0;

    virtual void sayHello() = 0;
};

class ElementEnglish: public IElement
{
public:
    void accept(Visitor &v) override;

    void sayHello() override;

    void sayHelloEnglish();
};

class ElementFrench: public IElement
{
public:
    void accept(Visitor &v) override;

    void sayHello() override;

    void sayHelloFrench();
};

} // visitor

} // design_pattern

#endif // __IELEMENT_H__
