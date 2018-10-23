#ifndef __IVISITOR_H__
#define __IVISITOR_H__

#include "IElement.h"

namespace design_pattern {

namespace visitor {

class IVisitor {
    public:
        void visit(IElementEnglish *element) = 0;
        void visit(IElementFrench *element) = 0;
};

} // Visitor
} // design_pattern

#endif
