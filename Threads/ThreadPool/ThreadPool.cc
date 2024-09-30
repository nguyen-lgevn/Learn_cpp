#include "ThreadPool.h"


ThreadPool::ThreadPool(int num_threads)
{
    std::cout << __FUNCTION__ << ":" << __LINE__ << std::endl;
    std::cout << __FUNCTION__ << ":" << __LINE__ << ": num of threads: " << std::thread::hardware_concurrency << std::endl;

    for(int i = 0; i < num_threads; i++)
        m_lst_worker_threads.emplace_back(std::thread(&ThreadPool::worker_loop, this));

}

ThreadPool::~ThreadPool()
{
    stop_all();
}

void ThreadPool::enqueue_job()
{

}

void ThreadPool::stop_all()
{
    std::unique_lock<std::mutex> lk();
    terminate_pool = true;
    cv.notify_all();

    for(auto &thread: m_lst_worker_threads)
        thread.join();

    m_lst_worker_threads.clear();
    stopped = true;
}

void ThreadPool::resume()
{

}

void ThreadPool::worker_loop()
{
    std::cout << __FUNCTION__ << ":" << __LINE__ << std::endl;
    while(true)
    {

    }
}

ThreadPool& ThreadPool::getInstance()
{
    std::cout << __FUNCTION__ << ":" << __LINE__ << std::endl;
    static ThreadPool instance(10);
    return instance;
}
