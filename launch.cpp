#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <string.h>
#include <limits.h>

using namespace std;

string exename;
string args;

#ifdef _WIN32
string getApplicationDirectory()
{
  char result[ MAX_PATH ];
  return string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}
#else
string getApplicationDirectory() 
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    std::string appPath = std::string( result, (count > 0) ? count : 0 );

    std::size_t found = appPath.find_last_of("/\\");
    return appPath.substr(0,found);
}
#endif

string get_current_dir()
{
   char buff[FILENAME_MAX]; //create string buffer to hold path
   getcwd( buff, FILENAME_MAX );
   string current_working_dir(buff);
   return current_working_dir;
}

int main(int argc,char* argv[]) 
{
    //args to std::string
    args= "";
    exename = argv[0];
    for (int i=1;i<argc;i++) args.append(std::string(argv[i]).append(" "));

    //print name
    cout << "Image Compressor v1.0" << endl;

    //concat command and run
	#ifdef _WIN32
	string total(string("java -Duser.dir=\"" + get_current_dir() + "\" -jar \"") + getApplicationDirectory() + "\" " + args);
	#else
    string total(string("java -Duser.dir=\"" + get_current_dir() + "\" -jar \"") + getApplicationDirectory() + "/" + exename + "\" " + args);
	#endif
    system(total.c_str());

    return 0;
}
