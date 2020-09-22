#ifndef __HELLOWORLD_NULLOBJECT_H__
#define __HELLOWORLD_NULLOBJECT_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldNullObject: public IHelloWorld {
public:
    void sayHello() override {

    }
};

} // design_patterns

#endif
