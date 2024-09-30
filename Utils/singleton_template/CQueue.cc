#include "CQueue.h"

CQueue::CQueue()
{
    std::cout << "CQueue constructor" << std::endl;
}

CQueue::~CQueue()
{
    std::cout << "CQueue destructor" << std::endl;
}

void CQueue::QueueAdd(int nDstQueueID, MsgQueue &msg)
{
    std::lock_guard<std::mutex> lock(m_mtx);
    if (nDstQueueID < 0)
        return;

    std::lock_guard<std::mutex> lk(m_queue_mtx);
    MsgQueue _msgQueue = msg;
    m_queue[nDstQueueID].push(_msgQueue);
    m_cv.notify_all();
}
 
bool CQueue::QueueGet(int nDest, MsgQueue& msg)
{
    std::cout << __FUNCTION__ << std::endl;
    while (1)
    {
        std::unique_lock<std::mutex> lk(m_queue_mtx);
        if (m_queue[nDest].size() == 0)
        {
           m_cv.wait(lk);
           lk.unlock();
        }
        else
        {
            break;  
        }
    }

    if (m_queue[nDest].size() > 0)
    {
        msg = m_queue[nDest].front();
        m_queue[nDest].pop();
        return true;
    }
    return false;
}

void CQueue::QueueClear()
{
}
