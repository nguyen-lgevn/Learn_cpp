#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
//#include "ThreadClass.h"
#include <future>

std::mutex m_mutex;
std::condition_variable m_cv;
std::string data;
bool ready = false;
bool process = false;

void worker_thread()
{
    std::unique_lock<std::mutex> lk(m_mutex);
    std::cout << "Start Thread" << std::endl;
    m_cv.wait(lk, []{return ready;});

    std::cout << "Worker thread is processing data\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    data += " after processing";

    process = true;
    std::cout << "Worker thread signals data processing completed\n";

    lk.unlock();
    m_cv.notify_one();
}

int main()
{
    
    //std::thread worker(worker_thread);

    auto f = std::async(worker_thread);
    data = "Example data";
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        ready = true;
        std::cout << "main() signals data ready for processing\n";
    }
    m_cv.notify_one();

    {
        std::unique_lock<std::mutex> lk(m_mutex);
        m_cv.wait(lk, []{return process;});
    }
    std::cout << "Back in main(), data = " << data << std::endl;

    //worker.join();
    
    /*
    ThreadClass t;
    t.start();

    {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Kill Thread" << std::endl;
        t.set_thread(true);
    }
    */

    //auto f = std::async(worker_thread);

    f.wait();
/*
    if (status == std::future_status::timeout)
    {
        std::cout << "time out\n";
    }
    else if (status == std::future_status::ready)
    {
        std::cout << "ready\n";
    }
    else
    {
        std::cout << "?\n";
    }
*/
    return 0;
}
