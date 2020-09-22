#ifndef __HELLOWORLD_FLYWEIGHT_H__
#define __HELLOWORLD_FLYWEIGHT_H__

#include "IHelloWorld.h"
#include <map>

namespace design_patterns {

class HelloWorldFlyweight: public IHelloWorld {
public:
    HelloWorldFlyweight(std::string _str): m_str(_str) {}

    void sayHello() override {
        std::cout << m_str << std::endl;
    }

private:
    std::string m_str;
};

class HelloWorldFlyweightFactory {
public:

    std::shared_ptr<IHelloWorld> getHelloWorld(std::string key)
    {
        if (m_helloWorldFlyweights.count(key) > 0)
            return m_helloWorldFlyweights[key];
        else
        {
            m_helloWorldFlyweights.insert(std::make_pair(key, std::make_shared<HelloWorldFlyweight>(key)));
            return m_helloWorldFlyweights[key];
        }
    }


private:

    std::map<std::string, std::shared_ptr<IHelloWorld>> m_helloWorldFlyweights;
};

} // design_patterns

#endif
