#include "ThreadPool.h"

int main(int argc, char **argv)
{
    std::cout << "Test Thread pool" << std::endl;
    ThreadPool::getInstance();
    return 0;
}
