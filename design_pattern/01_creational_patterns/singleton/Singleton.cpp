#ifndef __SINGLETON_H__
#define __SINGLETON_H__

namespace design_pattern {
namespace singleton {

class HelloWorldSingleton {
public:
    static HelloWorldSingleton getInstance();

private:
    HelloWorldSingleton();
    HelloWorldSingleton(const HelloWorldSingleton&) = delete; // copy constructor
    HelloWorldSingleton(HelloWorldSingleton&&) = delete; // move constructor
    HelloWorldSingleton& operator=(const HelloWorldSingleton&) = delete; // copy assign
    HelloWorldSingleton& operator=(HelloWorldSingleton&&) = delete; // move assign
};

} // singleton
} //design_pattern

#endif // __SINGLETON_H__
