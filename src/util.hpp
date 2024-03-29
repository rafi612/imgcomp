#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

using namespace std;

bool contains(string s1,string s2);
void get_files(vector<string> *ret,string path);
string remove_extension(string path);
string get_extension(string path);
uint64_t timeSinceEpochMillisec();
bool is_supported_image(string path);
const int get_format_id(string f);
int filesize(string s);
int get_dir_size(string dir);

#endif
