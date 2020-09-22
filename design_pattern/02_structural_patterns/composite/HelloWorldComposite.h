#ifndef __HELLOWOLRD_COMPOSITE_H__
#define __HELLOWOLRD_COMPOSITE_H__

#include "IHelloWorld.h"
#include <vector>

namespace design_patterns {

class HelloWorldComposite: public IHelloWorld {
public:
    void add(std::shared_ptr<IHelloWorld> helloWorld) {
        m_lstHelloWorld.push_back(helloWorld);
    }

    void sayHello() override {
        for(std::vector<std::shared_ptr<IHelloWorld>>::iterator it = m_lstHelloWorld.begin(); it != m_lstHelloWorld.end(); ++it)
        {
            (*it)->sayHello();
        }
    }

private:
    std::vector<std::shared_ptr<IHelloWorld>> m_lstHelloWorld;
};

class HelloWorldCompositeLeaf: public IHelloWorld {
public:
    void sayHello() override {
        std::cout << "Hello World Composite\n";
    }
};

} // design_patterns

#endif
