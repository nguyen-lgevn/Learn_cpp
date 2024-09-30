#include <iostream>

//extern "C" {
#include "posix_example.h"
}

int main (int argc, char *argv[]) {
    std::cout << "Start process: " << argv[1] << std::endl;
    /*
    int pid, status;
    if (pid = fork())
    {
        waitpid(pid, &status, 0);
    }
    else
    {
        const char executable[] = "/bin/ls";
        execl(executable, executable, "/" ,NULL);

    }
    */
    run_cmd(argv[1]);
    return 0;
}
