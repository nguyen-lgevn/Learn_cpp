#include <iostream>
#include <string>
#include <map>

std::map<std::string, std::string> map;

void checkMap(const char* key, const char* value)
{
    map[key] = value;
    std::cout << "key: " << key << " value: " << value <<  std::endl;
}

int main(int argc, char **argv)
{
    std::map<std::string, std::string> map;
    checkMap("test","1");
    return 0;
}
