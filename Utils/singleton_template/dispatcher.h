#ifndef __DISPATCHER_H_
#define __DISPATCHER_H_

#include <memory>
#include <iostream>
#include <map>
#include <functional>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T> (new T(std::forward<Args>(args)...));
}

typedef std::function<int(int, int, void*)> MsgHandler;

class dispatcher
{
public:
    dispatcher();
    ~dispatcher();

    int DispatcherHandler(int nCmd, int nInstId, void* pMsg);

    int RegHandler(int nCmd, MsgHandler fpHandler);

    void UnRegHandlerAll();

protected:
    std::map<int, MsgHandler> m_mapHandler;
};

#endif // __DISPATCHER_H_
