#ifndef __HELLOWORLD_STATE_H__
#define __HELLOWORLD_STATE_H__

#include "IHelloWorld.h"

namespace design_patterns {

class HelloWorldStateContext;

class IHelloWorldState {
public:
    virtual void goNext(std::shared_ptr<HelloWorldStateContext> _ptrContext) = 0;
};

class HelloWorldStateContext: public IHelloWorld, public std::enable_shared_from_this<HelloWorldStateContext> {
public:
    HelloWorldStateContext();

    void setState(std::shared_ptr<IHelloWorldState> _state)
    {
        m_ptrState = std::move(_state);
    }

    void sayHello() override {
        std::cout << m_strHelloWorld << std::endl;
    }

    void createWord(std::string _word) {
        m_strHelloWorld.append(_word);
    }

    std::shared_ptr<HelloWorldStateContext> process() {
        m_ptrState->goNext(shared_from_this());
        return shared_from_this();
    }

private:
    std::shared_ptr<IHelloWorldState> m_ptrState;
    std::string m_strHelloWorld;
};

class HelloWorldStateHello: public IHelloWorldState {
public:
    void goNext(std::shared_ptr<HelloWorldStateContext> _ptr);
};

class HelloWorldStateFinish: public IHelloWorldState {
public:
    void goNext(std::shared_ptr<HelloWorldStateContext> _ptr) {}
};

class HelloWorldStateWorld: public IHelloWorldState {
public:
    void goNext(std::shared_ptr<HelloWorldStateContext> _ptrContext) {
        _ptrContext->createWord("State");
        _ptrContext->setState(std::make_shared<HelloWorldStateFinish>());
    }
};

void HelloWorldStateHello::goNext(std::shared_ptr<HelloWorldStateContext> _ptrContext) {
    _ptrContext->createWord("Hello World ");
    _ptrContext->setState(std::make_shared<HelloWorldStateWorld>());
}

HelloWorldStateContext::HelloWorldStateContext() {
    m_ptrState = std::make_shared<HelloWorldStateHello>();
}

} // design_patterns

#endif
