#include "dispatcher.h"

dispatcher::dispatcher()
{
}

dispatcher::~dispatcher()
{
    m_mapHandler.clear();
}

int dispatcher::DispatcherHandler(int nCmd, int nInstId, void* pMsg)
{
    std::map<int, MsgHandler>::iterator itr;
    itr = m_mapHandler.find(nCmd);
    if (itr != m_mapHandler.end())
        return -1;

    MsgHandler pFunc = itr->second;
    return pFunc(nCmd, nInstId, pMsg);
}

int dispatcher::RegHandler(int nCmd, MsgHandler fpHandler)
{
    m_mapHandler[nCmd] = fpHandler;
    return 0;
}

void dispatcher::UnRegHandlerAll()
{
    m_mapHandler.clear();
}
