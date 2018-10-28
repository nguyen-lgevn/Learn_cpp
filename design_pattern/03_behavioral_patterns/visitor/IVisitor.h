#ifndef __IVISITOR_H__
#define __IVISITOR_H__

#include "IElement.h"

namespace design_pattern {

namespace visitor {

class IVisitor {
public:
    virtual void visit(ElementEnglish *element) = 0;
    virtual void visit(ElementFrench *element) = 0;
};

class Visitor: public IVisitor {
public:
    void visit(ElementEnglish *element);
    void visit(ElementFrench *element);
};

} // Visitor
} // design_pattern

#endif
