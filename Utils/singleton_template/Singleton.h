#ifndef __SINGLETON_H_
#define __SINGLETON_H_

#include <iostream>

template<typename T>
class Singleton {
public:
    static T& getInstance() {
        std::cout << "Singleton getInstance" << std::endl;
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    Singleton() {
        std::cout << "Singleton constructor" << std::endl;
    }
    
};

#endif // __SINGLETON_H_
