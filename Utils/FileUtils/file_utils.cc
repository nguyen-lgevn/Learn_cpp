#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <regex>

long long getTotalStorageMB(const char *path)
{
    long long total_size = 0;
    DIR* folder;
    struct dirent *next_file;
    struct stat buf;
    folder = opendir(path);
    if (folder == nullptr)
    {
        printf("Cannot open folder\n");
        return 0;
    }

    while ((next_file = readdir(folder)) != NULL)
    {
        // do not count current folder or parent folder
        if ((strcmp(next_file->d_name, ".") == 0) ||
                (strcmp(next_file->d_name, "..") == 0))
            continue;
        char file_path[1024];
        sprintf(file_path, "%s/%s", path, next_file->d_name);
        FILE* f = fopen(file_path, "r");
        if (fstat(fileno(f), &buf) == 0) // check stat is success
        {
            if (S_ISDIR(buf.st_mode))
                total_size += getTotalStorageMB(file_path);
            else
                total_size += buf.st_size;
        } else {
            //
        }
        fclose(f);
    }
    closedir(folder);
    return total_size;
}

void getFileCreationTime(const char *path)
{
    printf("Check directory %s\n", path);
    struct stat buf;
    struct dirent *next_file;
    DIR* folder = opendir(path);

    if (nullptr == folder)
    {
        printf("Cannot open folder\n");
        return;
    }
    while ((next_file = readdir(folder)) != NULL)
    {
        // do not count current folder or parent folder
        if ((strcmp(next_file->d_name, ".") == 0) || (strcmp(next_file->d_name, "..") == 0))
            continue;

        char file_path[1024];
        sprintf(file_path, "%s/%s", path, next_file->d_name);
        printf("file name: %s\t", file_path);
        FILE *f = fopen(file_path, "r");

        if (f != NULL)
        {
            if (0 == fstat(fileno(f), &buf))
            {
                char date[30];
                strftime(date, 30, "%d-%m-%y %H %M %S", localtime(&(buf.st_mtim.tv_sec)));
                printf("stat %s\n", date);
            }
        }
        fclose(f);
    }
    closedir(folder);
}

void checkModifiyTime(const char* folder_path)
{
    printf("checkAlbumArtImages() called\n");
    struct dirent *next_file;
    struct stat buf;

    // Open album artist directory
    DIR* folder = opendir(folder_path);
    if (nullptr == folder)
    {
        printf("cannot open dir");
        return;
    }
    else
    {
        while ((next_file = readdir(folder)) != NULL)
        {
            // do not count current/parent folder
            if ((strcmp(next_file->d_name, ".") == 0) || (strcmp(next_file->d_name, "..") == 0))
            {
                continue;
            }
            char path[1024];
            sprintf(path, "%s/%s", folder_path, next_file->d_name);
            printf("Full path of file: %s\n", path);
            // check stat of file
            if (lstat(path, &buf) >= 0)
            {
                auto time_d = std::chrono::seconds{buf.st_mtim.tv_sec} + std::chrono::nanoseconds{buf.st_mtim.tv_nsec};

                std::chrono::system_clock::time_point time_point {std::chrono::duration_cast<std::chrono::system_clock::duration>(time_d)};
                auto current_time = std::chrono::system_clock::now();
                auto in_time_t = std::chrono::system_clock::to_time_t(current_time);
                std::string s(30, '\0');
                std::strftime(&s[0], s.size(), "%Y-%m-%d %H:%M:%S", std::localtime(&in_time_t));
                printf("checkAlbumArtImages() current time %s\n", s.c_str());

                std::time_t modified_time = std::chrono::system_clock::to_time_t(time_point);
                std::string str_modified_time(30, '\0');
                std::strftime(&str_modified_time[0], str_modified_time.size(), "%Y-%m-%d %H:%M:%S\n", std::localtime(&modified_time));
                printf("checkAlbumArtImages() file [%s] time %s\n", next_file->d_name, str_modified_time.c_str());

                std::chrono::duration<double> elapsed_seconds = current_time - time_point;
                printf("checkAlbumArtImages() file [%s] time of exist %f\n", next_file->d_name, elapsed_seconds.count());
                if (elapsed_seconds.count() >= 5*60.0)
                {
                    printf("checkAlbumArtImages() delete file [%s]\n", next_file->d_name);
                    //remove(path);
                }
            }
        }
        closedir(folder);
    }
}

std::string readFileContent(std::string& fileName)
{
    std::string str;
    std::ifstream ifs(fileName);
    if (ifs.good() == true)
    {
        str.assign(std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()) );
    }
    else
    {
        std::cout << "Cannot open file"  << std::endl;
    }
    return str;
}

std::string trimSpace(std::string str)
{
    const char* spaceChars = " \n\r";
    size_t first = str.find_first_not_of(spaceChars);
    if (first == std::string::npos)
    {
        return "";
    }
    size_t last = str.find_last_not_of(spaceChars);
    return str.substr(first, (last+1)-first);
}

void change_file_content(const std::string& fileName, const std::string& strAppRegion)
{
    std::string strCfgFilePath = "";
    std::ifstream ifs(fileName);
    std::vector<std::string> lines;
    std::cout << strAppRegion << std::endl;

    std::string strLine;
    std::string newContent = "appRegion=" + strAppRegion;
    std::string strKeyword = "appRegion";

    if (ifs.is_open() == true)
    {
        while (std::getline(ifs, strLine))
        {
            strLine = trimSpace(strLine);
            size_t pos = strLine.find(strKeyword);
            if (pos != std::string::npos)
            {
                std::cout << "FOUND" << std::endl;
                strLine = newContent;
                std::cout << strLine << std::endl;
            }
            lines.push_back(strLine);
        }

    }
    ifs.close();
    std::ofstream ofs(fileName);
    if (ofs.is_open())
    {
        ofs.clear();
        for(auto line: lines)
        {
            ofs.write((line + "\n").c_str(), line.size() + 1);
        }
    }
    else
    {
    }
    ofs.close();
}

int main(int argc, char* argv[])
{
    //printf("%ld\n",getTotalStorageMB(argv[1]));
    //getFileCreationTime(argv[1]);

    //printf("Start main: %d %s", argc, argv[1]);
    //checkModifiyTime(argv[1]);
    //
    std::string fileName (argv[1]);
    std::string strAppRegion(argv[2]);
    change_file_content(fileName, strAppRegion);
    return 0;
}
