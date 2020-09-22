#ifndef __HELLOWORLD_OBSERVER_H__
#define __HELLOWORLD_OBSERVER_H__

namespace design_patterns {

class HelloWorldObserver;

class HelloWorldObserverSubject {
public:
    void attach(std::shared_ptr<HelloWorldObserver> _observer) {
        m_lstObservers.push_back(_observer);
    }

    void notify();

    void setHelloWorld(std::string _strHelloWorld)
    {
        m_strHelloWorld = _strHelloWorld;
        notify();
    }

    std::string getHelloWorld()
    {
        return m_strHelloWorld;
    }

private:
    std::vector<std::shared_ptr<HelloWorldObserver>> m_lstObservers;
    std::string m_strHelloWorld;
};

class HelloWorldObserver: public std::enable_shared_from_this<HelloWorldObserver> {
public:
    void setSubject(std::shared_ptr<HelloWorldObserverSubject> _ptrSub)
    {
        m_ptrSub = std::move(_ptrSub);
        m_ptrSub->attach(shared_from_this());
    }

    void update() {
        std::cout << m_ptrSub->getHelloWorld() << std::endl;
    }

private:
    std::shared_ptr<HelloWorldObserverSubject> m_ptrSub;
};

void HelloWorldObserverSubject::notify() {
    for(auto it = m_lstObservers.begin(); it != m_lstObservers.end(); ++it)
    {
        (*it)->update();
    }
}

} // design_patterns

#endif
