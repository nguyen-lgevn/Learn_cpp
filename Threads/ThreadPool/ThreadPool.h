#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>
#include <queue>
#include <chrono>

class ThreadPool {
    public:
        static ThreadPool& getInstance();

        void enqueue_job();

        void stop_all();
        void resume();

        void worker_loop();

        // for singleton
        ThreadPool(ThreadPool const&)               = delete;
        ThreadPool(ThreadPool&&)                    = delete;
        ThreadPool& operator=(ThreadPool const&)    = delete;
        ThreadPool& operator=(ThreadPool&&)         = delete;

    protected:
        ThreadPool(int num_threads);
        ~ThreadPool();

    private:
        std::vector<std::thread> m_lst_worker_threads;

        bool terminate_pool;
        bool stopped;
        std::condition_variable cv;
};

#endif // __THREAD_POOL_H__
