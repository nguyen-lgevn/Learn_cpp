#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <string>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf(ANSI_COLOR_RED "Usage: please provide the url" ANSI_COLOR_RESET "\n");
        return -1;
    }

    char* link = argv[1];
    printf("%s Open link %s %s\n",ANSI_COLOR_GREEN, link, ANSI_COLOR_RESET);

    CURL *curl;
    CURLcode res;
    std::string s;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) 
    {
        curl_easy_setopt(curl, CURLOPT_URL, link);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_content);

        res= curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }
    else
    {
        printf("%sCannot init curl%s\n", ANSI_COLOR_RED,ANSI_COLOR_RESET);
    }
    curl_global_cleanup();
    return 0;
}
