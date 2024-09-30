#include <iostream>
#include <future>
#include <thread>

static int i = 0;

int foo()
{
    i++;
    return i;
}

int main(int argc, char **argv)
{
    std::packaged_task<int()> task(&foo);
    std::future<int> f1 = task.get_future();
    std::thread t(std::move(task));

    std::future<int> f2 = std::async(std::launch::async, &foo);

    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread([&p]{p.set_value_at_thread_exit(3);}).detach();

    std::cout << "Waiting..." << std::endl;
    f1.wait();
    f2.wait();
    f3.wait();

    std::cout << "Done.\n Result: " << f1.get() << " " << f2.get() << " " << f3.get() << std::endl;

    t.join();
    return 0;
}
