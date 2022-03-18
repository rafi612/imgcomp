#ifndef UTIL_H
#define UTIL_H

#include <vector>

using namespace std;

void get_files(std::vector<std::string> *ret,std::string path);
string remove_extension(string path);
string get_extension(string path);
int get_dir_size(string dir);
uint64_t timeSinceEpochMillisec();
bool is_supported_image(string path);
const int get_format_id(string f);

#endif
