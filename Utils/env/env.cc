#include <iostream>
#include <cstdlib>

int main()
{
    if (const char* env_p = std::getenv("PATH"))
    {
        std::cout << "PATH is: " << env_p << std::endl;
    }
    return 0;
}
