#include <vector>
#include <cstdlib>
#include <string>
#include <dirent.h>
#include <fstream>
#include <filesystem>
#include <chrono>

#include "util.h"
#include "imgcomp.h"

#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

using namespace std;

bool is_dir(string path)
{
    DIR* directory = opendir(path.c_str());
    return directory != NULL;
}

void get_files(vector<string> *ret,string path)
{
    struct dirent **namelist;
    int n;

    n = scandir(path.c_str(), &namelist, 0, alphasort);
    if (n < 0)
       perror("scandir");
    else
    {
       while (n--)
       {
            const char* name = namelist[n]->d_name;

            if (string(name) != "." && string(name) != "..")
            {
                if(is_dir(string(path + PATH_SEPARATOR + name)))
                    get_files(ret,path + PATH_SEPARATOR + name);
                else ret->push_back(string(path + PATH_SEPARATOR + name));
            }
            free(namelist[n]);
       }
       free(namelist);
    }
}

string remove_extension(string path)
{
    size_t lastindex = path.find_last_of(".");
    return path.substr(0, lastindex);
}

string get_extension(string path)
{
    std::filesystem::path filePath = path;
    return filePath.extension();
}

int filesize(string filename)
{
    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

int get_dir_size(string dir)
{
    vector<string> files;
    get_files(&files,dir);
    int size;
    for (string file : files)
        size += filesize(file);
    return size;
}

uint64_t timeSinceEpochMillisec()
{
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

bool is_supported_image(string path)
{
    return get_extension(path) == ".png" || get_extension(path) == ".jpg" || get_extension(path) == ".bmp";
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
    return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

const int get_format_id(string f)
{
    switch(str2int(f.c_str()))
    {
    case str2int("png"):
        return PNG;
    case str2int("jpg"):
        return JPG;
    case str2int("bmp"):
        return BMP;
    default:
        return -1;
    }
}
