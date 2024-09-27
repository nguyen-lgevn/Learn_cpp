#include <iostream>
#include "includes/Operators.h"
#include "includes/Types.h"
#include <vector>
#include <list>
#include <algorithm>
#include <sstream>

int main(int argc, char **argv)
{
    std::size_t size;
    if (argc == 1)
    {
        std::cout << "no params - use default size" << std::endl;
        size = 20000;
    }
    else
    {
        std::cout << "use size: " << argv[1]  << std::endl;
        std::istringstream iss(argv[1]);
        iss >> size;
    }
    std::cout << "Fill back test size: " << size << std::endl;
    bench<std::vector<int>,Empty,Filled >("std::vector" ,size);
    bench<std::list<int>,Empty,Filled >("std::list", size);
    bench<std::deque<int>,Empty,Filled >("std::deque", size);
    bench<std::vector<int>,Empty,FillBackInserter>("std::vector" ,size);
    bench<std::vector<int>,Empty, Reserve, Filled>("std::vector reserve" ,size);
    bench<std::list<int>,Empty,FillBackInserter>("std::list" ,size);
    bench<std::deque<int>,Empty,FillBackInserter>("std::deque" ,size);

    std::cout << "\nEmplace back test size: " << size << std::endl;
    bench<std::vector<int>,Empty, EmplaceBack >("std::vector" ,size);
    bench<std::list<int>,Empty, EmplaceBack >("std::list" ,size);
    bench<std::deque<int>,Empty, EmplaceBack >("std::deque" ,size);

    std::cout << "\nFill Front test size: " << size << std::endl;
    bench<std::vector<int>, Empty, FillFront>("vector fill front", size);
    bench<std::list<int>, Empty, FillFront>("list fill front", size);
    bench<std::deque<int>, Empty, FillFront>("deque fill front", size);

    std::cout << "\nEmplace front test size: " << size << std::endl;
    bench<std::vector<int>,Empty, EmplaceFront >("std::vector emplace front" ,size);
    bench<std::list<int>,Empty, EmplaceFront >("std::list emplace front" ,size);
    bench<std::deque<int>,Empty, EmplaceFront >("std::deque emplace front" ,size);

    std::cout << "\nLinear Search test size: " << size << std::endl;
    bench<std::vector<int>, FilledRandom, Find >("std::vector search" ,size);
    bench<std::list<int>, FilledRandom, Find>("std::list search" ,size);
    bench<std::deque<int>, FilledRandom, Find >("std::deque search" ,size);

    std::cout << "\nSort test size: " << size << std::endl;
    bench<std::vector<int>, FilledRandom, Sort >("std::vector sort" ,size);
    bench<std::list<int>, FilledRandom, Sort>("std::list sort" ,size);
    bench<std::deque<int>, FilledRandom, Sort>("std::deque sort" ,size);

    std::cout << "\nReverse test size: " << size << std::endl;
    bench<std::vector<int>, Filled, Reverse >("std::vector reverse" ,size);
    bench<std::list<int>, Filled, Sort>("std::list reverse" ,size);
    bench<std::deque<int>, Filled, Sort>("std::deque reverse" ,size);
    return 0;
}
