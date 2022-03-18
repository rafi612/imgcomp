#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include <filesystem>
#include <chrono>

#include "util.h"
#include "imgcomp.h"

using namespace std;
namespace fs = std::filesystem;

void get_files(vector<string> *ret,string path)
{
    for (const auto & entry : fs::directory_iterator(path))
    {
        if (fs::is_directory(entry.path().u8string()))
            get_files(ret,entry.path().u8string());
        else
            ret->push_back(entry.path().u8string());
    }
}

string remove_extension(string path)
{
    size_t lastindex = path.find_last_of(".");
    return path.substr(0, lastindex);
}

string get_extension(string path)
{
    fs::path filePath = path;
    return filePath.extension().u8string();
}

int get_dir_size(string dir)
{
    vector<string> files;
    get_files(&files,dir);
    int size;
    for (string file : files)
        size += fs::file_size(file);
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
