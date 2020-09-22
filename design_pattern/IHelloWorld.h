#ifndef __IHELLO_WORLD_H__
#define __IHELLO_WORLD_H__

#include <iostream>
#include <memory>
#include <vector>

namespace design_patterns {

class IHelloWorld {
public:
    virtual void sayHello() = 0;
};

} // design_patterns

#endif
