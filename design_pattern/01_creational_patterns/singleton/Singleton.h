#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace design_pattern {
namespace singleton {

class HelloWorldSingleton {
public:
    static HelloWorldSingleton& getInstance();

    HelloWorldSingleton(HelloWorldSingleton const&) = delete; // Copy constructor
    HelloWorldSingleton(HelloWorldSingleton&&) = delete; // Move constructor
    HelloWorldSingleton& operator=(HelloWorldSingleton const&) = delete; // Copy assign
    HelloWorldSingleton& operator=(HelloWorldSingleton&&) = delete; // Move assign

private:

protected:
    HelloWorldSingleton();
}

} // singleton
} // design_pattern

#endif // __SINGLETON_H__
