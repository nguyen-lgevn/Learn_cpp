#ifndef __HELLOWORLD_OBJECTPOOL_H__
#define __HELLOWORLD_OBJECTPOOL_H__

#include "IHelloWorld.h"
#include <list>

namespace design_patterns {

class HelloWorldResource: public IHelloWorld {
public:
    void sayHello() override {
        std::cout << m_strHelloWorld << std::endl;
    }

    void reset() {
        m_strHelloWorld.clear();
    }

    void setHelloWorld(std::string _str) {
        m_strHelloWorld = _str;
    }

    std::string getHelloWorld() {
        return m_strHelloWorld;
    }

private:
    std::string m_strHelloWorld;
};

class HelloWorldObjectPool {
public:
    static HelloWorldObjectPool& getInstance() {
        static HelloWorldObjectPool instance;
        return instance;
    }

    std::unique_ptr<HelloWorldResource> getResource() {
        if (m_lstResources.empty())
        {
            return std::move(std::make_unique<HelloWorldResource>());
        }
        else
        {
            std::unique_ptr<HelloWorldResource> res = std::move(m_lstResources.front());
            m_lstResources.pop_front();
            return res;
        }
    }

    void returnResource(std::unique_ptr<HelloWorldResource> _ptrRes) {
        _ptrRes->reset();
        m_lstResources.emplace_back(std::move(_ptrRes));
    }

private:
    HelloWorldObjectPool() = default;
    HelloWorldObjectPool(const HelloWorldObjectPool&) = delete;
    HelloWorldObjectPool& operator=(const HelloWorldObjectPool&) = delete;

    std::list<std::unique_ptr<HelloWorldResource>> m_lstResources;
};

} // design_patterns

#endif
