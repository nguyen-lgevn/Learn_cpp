#ifndef _CQUEUE_H_
#define _CQUEUE_H_

#include <iostream>
#include "Singleton.h"
#include <queue>
#include <memory>
#include <mutex>
#include <thread>
#include <condition_variable>

enum  QueueType {
    REC_EVT = 0,
    SEND_EVT,
    MAX_EVT
};

template<typename T>
class MsgQueue {

};

class CQueue: public Singleton<CQueue>
{
public:
    friend class Singleton<CQueue>;

    void QueueAdd(int nDstQueueID, MsgQueue &msg);
    bool QueueGet(int nDest, MsgQueue& msg);
    void QueueClear();
private:
    CQueue();
    ~CQueue();
    std::queue<MsgQueue> m_queue[QueueType::MAX_EVT];

    std::mutex m_mtx;
    std::mutex m_queue_mtx;
    std::condition_variable m_cv;
};

#endif // _CQUEUE_H_
