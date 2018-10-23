#ifndef __IELEMENT_H__
#define __IELEMENT_H__

namespace design_pattern {

namespace visitor {

class IElement {
public:
    virtual void accept(class Visitor &v) = 0;

    virtual void sayHello() = 0;
};

class IElementEnglish: public IElement
{
public:
    void accept(Visitor &v) override;

    void sayHello() override;

    void sayHelloEnglish();
};

class IElementFrench: public IElement
{
public:
    void accept(Visitor &v) override;

    void sayHello() override;

    void sayHelloFrench();
};

} // visitor

} // design_pattern

#endif // __IELEMENT_H__
