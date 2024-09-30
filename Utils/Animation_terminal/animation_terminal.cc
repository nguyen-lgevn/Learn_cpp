#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

int main(int argc, char** argv)
{
    std::cout << "Progress in terminal\n";
    std::cout << "#-" << std::setw(100) << "[0%]" << std::flush;
    int i = 0; 
    for(;;)
    {
        i++;
        std::string s(i, '#');
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\r" << s << "\b\\" << std::setw(100 - i) << "[" << i << "%]" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\r" << s << "\b|" << std::setw(100 - i) << "[" << i << "%]" << std::flush;
        //std::cout << "\b|" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\r" << s << "\b/" << std::setw(100 - i) << "[" << i << "%]" << std::flush;
        //std::cout << "\b/" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout << "\r" << s << "\b-" << std::setw(100 - i) << "[" << i << "%]" << std::flush;
        //std::cout << "\b-" << std::flush;
        //std::cout << "\b#-";
        if (i == 100) break;
    }
    return 0;
}
