#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
enum ErrorType {noError, immediateFailure, returnFailure, forkFailure};

int run(void)
{
    int error = noError;
    char proc[] = "/usr/bin/Idontexist";
    char *const params[] = {proc, NULL};

    size_t sz = 32*(size_t)(1024*1024*1024);
    char *p = (char*)malloc(sz);
    memset(p, 0, sz);

    pid_t pid = fork();

    printf("pid = %d\n", pid);

    if (pid == 0)
    {
        if (execv(proc, params) == -1)
        {
            error = immediateFailure;
        }
        printf("child error: %d\n");
        _exit(error);
    }
    else if (pid > 0)
    {
        int waitError;
        waitpid(pid, &waitError, 0);
        if (waitError)
            error = returnFailure;

        printf("parrent error = %d, waitError = %d\n", error, waitError);
    }
    else
    {
        error = forkFailure;
    }

    return error;
}

int main(int argc, char **argv)
{
    printf("run() = %d\n", run());
    return 0;
}
