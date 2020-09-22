#include <iostream>
#include <thread>
#include <chrono>
//#include <future>
#include <mutex>
//#include <cstring>
//#include <ratio>
#include "Utils/UtilsFunction.h"
#include <functional>
#include <list>
#include <condition_variable>
#include <ctime>
//#include <iomanip>
//#include <time.h>
#include <algorithm>

/*
void demo(const char* lhs, const char* rhs, int sz)
{
    int rc = std::strncmp(lhs, rhs, sz);
    if (rc == 0)
        std::cout << "equal" << std::endl;
    else
        std::cout << "not equal" << std::endl;
}

uint8_t high_uint8(uint16_t combined)
{
    return combined >> 8u;
}

uint8_t low_uint8(uint16_t combined)
{
    uint16_t mask = std::numeric_limits<uint8_t>::max();
    return mask & combined;
}

uint16_t combine_uint16(uint8_t low, uint8_t high)
{
    return ((((uint16_t) high) << 8u) | (uint16_t)low);
}

#define PERSISTENCY_KEY_ANALOG_LASTINFO_AM_FREQ         "LASTINFO_ANALOG_AM_FREQ" 

int maxLength(const char* str1, const char* str2) {
    return (strlen(str1) > strlen(str2)) ? strlen(str1) : strlen(str2);
}

#define STR1 "s"
#define STR2 "m"
//#define CONCATE(str1, str2) str1 ## str2
#define STR STR1 STR2
*/

//template<typename Duration>
void print_time()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();
    tp -= std::chrono::duration_cast<std::chrono::seconds>(tp);
    std::time_t ttp = std::chrono::system_clock::to_time_t(now);
    tm t = *gmtime(&ttp);

    std::printf("[%04u-%02u-%02u %02u:%02u:%02u.%03u]: ", t.tm_year + 1900,
                t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
                static_cast<unsigned>(tp/std::chrono::milliseconds(1)));
}

template<typename T, typename... Args>
struct FunctionType
{
    typedef std::function<T(Args...)> TimerCallback;
};

typedef std::function<void(int)> TimerCallback;

struct TimerItem {
    int id;
//    TimerCallback cb;
    TimerCallback cb;
    std::chrono::time_point<std::chrono::system_clock> until;
};

bool compareTimerItem(std::shared_ptr<TimerItem> lhs, std::shared_ptr<TimerItem> rhs)
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(lhs->until - rhs->until).count() < 0 ? true: false;
}


// bool ready = false;

class TimerQueue {

public:

    virtual ~TimerQueue() {
        if (m_thread.joinable())
            m_thread.join();
    }
    TimerQueue(const TimerQueue&) = delete;
    TimerQueue& operator=(TimerQueue&) = delete;

    static std::shared_ptr<TimerQueue> getInstance() {
        static std::shared_ptr<TimerQueue> instance(new TimerQueue);
        return instance;
    }

    void setTimer(int id, long milliseconds, TimerCallback cb)
    {
        print_time();
        std::cout << __FUNCTION__ << "id: " << id << "\ttimer: " << milliseconds << std::endl;

        std::unique_lock<std::mutex> lk_cd(m_timerListMtx);
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        std::chrono::time_point<std::chrono::system_clock> until = now + std::chrono::milliseconds(milliseconds);
        std::shared_ptr<TimerItem> item = std::make_shared<TimerItem>();
        item->id = id;
        item->cb = cb;
        item->until = until;
        {
            if (isTimerExist(id) == false)
            {
                std::lock_guard<std::mutex> lk(m_queueMtx);
                m_timerList.push_back(item);
                m_timerList.sort(compareTimerItem);
                TimerQueue::m_timer_ready = true;
            }
        }
        lk_cd.unlock();
        m_cvTimerList.notify_one();
    }

    void removeTimer(int id)
    {
        std::lock_guard<std::mutex> lk(m_queueMtx);

        std::shared_ptr<TimerItem> item;
        std::list<std::shared_ptr<TimerItem>>::iterator it = m_timerList.begin();
        while (it != m_timerList.end())
        {
            item = *it;
            if (item->id == id)
            {
                it = m_timerList.erase(it);
                break;
            }
            else
            {
                ++it;
            }
        }
    }

    bool isTimerExist(int id)
    {
        std::lock_guard<std::mutex> lk(m_queueMtx);
        bool result = false;
        std::shared_ptr<TimerItem> item;
        std::list<std::shared_ptr<TimerItem>>::iterator it = m_timerList.begin();
        while (it != m_timerList.end())
        {
            item = *it;
            if (item->id == id)
            {
                result = true;
                break;
            }
            else
            {
                ++it;
            }
        }
        return result;
    }

    static bool m_timer_ready;

private:
    TimerQueue() {
        std::cout << "Timer Queue constructor\n";
        m_thread = std::thread(&TimerQueue::start, this);
//        m_thread.join();
    }

    void start()
    {
        std::cout << "Start thread\n";
        std::shared_ptr<TimerItem> item;
        while (true)
        {
            if (m_timerList.empty() == true)
            {
//                std::cout << "timer list is empty\n";
                std::unique_lock<std::mutex> lk(m_timerListMtx);
                m_cvTimerList.wait(lk, []{return TimerQueue::m_timer_ready;});
            }
            else
            {
                {
                    std::lock_guard<std::mutex> lk(m_queueMtx);
                    item = m_timerList.front();
                }
                {
                    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
                    auto count_down = std::chrono::duration_cast<std::chrono::milliseconds>(item->until - now);
//                    std::cout << "Count down: " << count_down.count() << std::endl;
                    if (count_down.count() <= 0)
                    {
                        item->cb(item->id);
                        {
                            std::lock_guard<std::mutex> lk(m_queueMtx);
                            m_timerList.pop_front();
                        }
                    }
                }
            }
        }
    }

    std::list<std::shared_ptr<TimerItem>> m_timerList;
    std::mutex m_timerListMtx;
    std::mutex m_queueMtx;
    std::condition_variable m_cvTimerList;
    std::thread m_thread;
};

void foo(int num)
{
    print_time();
    std::cout << " Foo: " << num << std::endl;
}

void bar(std::string str)
{
    print_time();
    std::cout << "Bar: " << str << std::endl;
}

//void add_timer()
//{
//    long ms = 1000;
//
//    TimerCallback cb = foo;
//
//    for (int i = 1; i < 10; ++i)
//    {
//        TimerQueue::getInstance()->setTimer(i, ms * i, cb);
//        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//    }
///*
//    FunctionType<std::string>::TimerCallback cb_temp = bar;
//    for (int i = 1; i < 10; ++i)
//    {
//        TimerQueue::getInstance()->setTimer(i, ms * i, cb_temp);
//        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//    }
//*/
//}

//bool TimerQueue::m_timer_ready = false;

std::string iso88951ToUtf8(const uint8_t* buffer, const int bufferSize)
{
    std::string utf8;

    utf8.reserve(1 + (2 * bufferSize));

    for (int i = 0 ; (i < bufferSize) && (0x0 != buffer[i]); i++)
    {
        unsigned char c = buffer[i];

        if (c <= 0x1F) // do not use character in range 0x00~0x1F
        {
            utf8 += " ";
        }
        else if ((c < 0x80) && (c > 0x1F))
        {
            utf8 += static_cast<char>(buffer[i]);
        }
        else if ((c >= 0x80) && (c <= 0x9F)) // do not use character in range 0x80~0x9F
        {
            utf8 += " ";
        }
        else if (c < 0xC0)
        {
            utf8 += static_cast<char>(0xc2);
            utf8 += static_cast<char>(buffer[i]);
        }
        else
        {
            utf8 += static_cast<char>(0xc3);
            utf8 += static_cast<char>(buffer[i] - 0x40);
        }
    }

    return utf8;
}

struct Foo {
    int a;
    int b;

    Foo (int _a, int _b) {a=_a;b=_b;}
};

int main(int argc, char *argv[])
{
    //std::list<Foo> lst;
    //Foo f(2,3);
    
    //lst.push_back(f);
    /*
    Foo f1(2,4);
    Foo f2(3,5);
    lst.push_back(f1);
    lst.push_back(f2);
    */
    /*
    std::cout << lst.size() << std::endl;
    auto last = std::unique(lst.begin(), lst.end(), [](const Foo& first, const Foo& second) {
            std::cout << first.b << " " << second.b << std::endl;
            return first.b == second.b;
        });
    if (last != lst.end())
        std::cout << "There is a duplicate\n";
    else
        std::cout << "There is no duplicate\n";
    lst.erase(last, lst.end());

    std::cout << lst.size() << std::endl;
    for (std::list<Foo>::iterator it = lst.begin(); it != lst.end(); ++it)
    {
        std::cout << (*it).a << " " << (*it).b << std::endl;
    }
    */
    //demo("Hello, world!", "Hello, everybody!", 13);
    //demo("", "", 1);
    //demo("H", "", 13);

    /*
    uint8_t hi = Utils::CommonFunction::byte_hi(9550);
    uint8_t lo = Utils::CommonFunction::byte_low(9550);
    uint16_t comb = Utils::CommonFunction::make_hword(hi, lo);
    //std::cout << "hi: " << unsigned(hi) << "low: " << unsigned(lo) << "combine: " << comb << std::endl;
    printf("hi: 0x%x\n", hi);
    printf("low: 0x%x\n", lo);
    printf("combine: 0x%d\n", comb);
   
    Utils::CommonFunction::printBits(9550);
    Utils::CommonFunction::printBits(hi);
    Utils::CommonFunction::printBits(lo);
    Utils::CommonFunction::printBits(comb);
    */

    int x = 0;
    Utils::CommonFunction::printBits(x);
    //int y = 0;
    for (int i = 0; i < 8; i++)
    {
        x = x | (1 << i);
        Utils::CommonFunction::printBits(x);
        printf("%d\n", x);
    }

    /*
    std::cout << sizeof(PERSISTENCY_KEY_ANALOG_LASTINFO_AM_FREQ) << "  " << strlen(PERSISTENCY_KEY_ANALOG_LASTINFO_AM_FREQ) << std::endl;

    const char* key = "LASTINFO_ANALOG_AM_FREQ";
    const char* key1 = "LASTINFO_ANALOG_AM_FREQ_111";
    if (strncmp(key, PERSISTENCY_KEY_ANALOG_LASTINFO_AM_FREQ,
      maxLength(key, PERSISTENCY_KEY_ANALOG_LASTINFO_AM_FREQ)) == 0) {
	std::cout << "Equal" << std::endl;
    }
    else {
	std::cout << "Not Equal" << std::endl;
    }

    if (strncmp(key1, PERSISTENCY_KEY_ANALOG_LASTINFO_AM_FREQ,
      maxLength(key1, PERSISTENCY_KEY_ANALOG_LASTINFO_AM_FREQ)) == 0) {
	std::cout << "Equal" << std::endl;
    }
    else {
	std::cout << "Not Equal" << std::endl;
    }
    */

//    std::chrono::duration<int, std::ratio<60*60*24> > timeout(1);

//    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
//    std::chrono::system_clock::time_point until = now + timeout;
//    std::cout << std::chrono::duration_cast<std::chrono::minutes>(until - now).count() << std::endl;


//    std::thread t(add_timer);
//    t.join();

//    uint8_t* array;
//    array = (uint8_t*)malloc(35 * sizeof(uint8_t));
//    if (array != NULL)
//    {
//        array[0] = 0x20;
//        array[1] = 0x62;
//        array[2] = 0x79;
//    }
//    std::string res = iso88951ToUtf8(array, 35);   
//    std::cout << res << std::endl;
    return 0;
}
