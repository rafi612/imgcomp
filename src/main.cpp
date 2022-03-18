#include <iostream>
#include <filesystem>

#include "util.h"
#include "imgcomp.h"

#define VERSION "2.0"

using namespace std;
namespace fs = std::filesystem;

bool keepfiles,names;
string source;
string format;
double divider = 0;

bool contains(string s1,string s2)
{
    return s1.find(s2) != string::npos;
}

void help()
{
    cout << "Usage: imgcomp -<flags> <folder or image path> <divider> <format>" << endl;
    cout << "Flags: -k - keep original files" << endl;
    cout << "Flags: -n - keep original names on compressed files" << endl;
    cout << "Flags: -help - shows how to use imgcomp" << endl;
    cout << "Flags use: -xyz" << endl;
    cout << "If you dont use flags use: imgcomp <folder or image path> <divider> <format>" << endl;
    cout << "Divider: Resolution was divided by divider" << endl;
    cout << "Format: png/jpg/bmp etc.. (jpg recomended)" << endl;

}

void compress(string file,double d,string f)
{
    cout << "Searching files..." << endl;

    vector<string> files;
    if (fs::is_directory(file)) get_files(&files,file);
    else files.push_back(file);

    int sizebefore = fs::is_directory(file) ? get_dir_size(file) : fs::file_size(file);

    cout << files.size() << " files found in all directories and subdirectories" << endl;
    cout << "Size total:" << (sizebefore / 1000 / 1000) << "MB (" << sizebefore << " Bytes)" << endl;

    if (keepfiles)
    {
        cout << "Copying original files..." << endl;
        if (fs::is_directory(file))
            fs::copy(file,string(file + "-original"));
        else
            fs::copy(file,string(remove_extension(file) + "-original" + get_extension(file)));
    }

    int percent;
    uint64_t startTime = timeSinceEpochMillisec() / 1000;
    int compressedFiles = 0;
    int elapsedTime = 0;

    string filenameaddon = "-compress.";
    if (names) filenameaddon = ".";

    for (int i = 0; i < files.size();i++)
	{
        percent = (int)((double)i / (double)files.size() * (double)100);
        elapsedTime = (timeSinceEpochMillisec() / 1000) - startTime;
        int allTimeForCompressing = (elapsedTime * files.size() / (compressedFiles + 1));
        int remainingTime = allTimeForCompressing - elapsedTime;

        if (!fs::is_directory(files[i]))
        {
            if (is_supported_image(files[i]))
            {
                cout << "Compressed: " << percent << "% Elapsed: " << elapsedTime << "s ETA: " << remainingTime << "s" << endl;
                
                //load
                int w,h,comp;
                unsigned char* image = load_image(files[i],&w,&h,&comp,get_format_id(f));

                //remove old file
                fs::remove(files[i]);
                
                //output path
                string output = remove_extension(files[i]) + filenameaddon + f;

                //resize
                int out_w, out_h, dest_chan;
                unsigned char* out_image = compress_image(image,w,h,comp,d,get_format_id(f),&out_w,&out_h,&dest_chan);

                //write
                write_image(output,out_image,out_w,out_h,dest_chan,get_format_id(f));

                cout << "Compressed " << files[i] << " -> " << output << endl;
			    compressedFiles++;
            }
            else cout << "Skipped " << files[i] << endl;
        }
	}

    cout << endl << "Compression Complete!!!" << endl;
	cout << "Searching files..." << endl << endl;
	int sizeafter = get_dir_size(source);

	cout << "Total time:" << elapsedTime << "s" << endl;
	cout << "Size before:" << (sizebefore / 1000 / 1000) << "MB (" << sizebefore << " Bytes)" << endl;
	cout << "Size after:" << (sizeafter / 1000 / 1000) << "MB (" << sizeafter << " Bytes)" << endl;

	double ratio = (int)((double)sizeafter / (double)sizebefore * (double)100);
	cout << "Lossy compression ratio: " << ratio << "%" << endl;
}

int main(int argc, char *argv[])
{
    cout << "Image Compressor " << VERSION << endl;

    string flags;
    if (argc == 1)
    {
       help();
       return 0;
    }
    else
    {
        int move;
        flags = argv[1];
        if (argc >= 2)
        {
            //starts With
            if (flags.find("-") == 0) move = 0;
            else move = 1;

            source = argv[2- move];
			divider = atof(argv[3 - move]);
			format = argv[4 - move];

            if (divider == 0) divider = 1;
        }
		if (move == 0)
		{
			if(contains(flags,"k"))//k
				keepfiles = true;

			if(contains(flags,"n"))//n
				names = true;
		}

        if (contains(flags,"-help"))
           help();
    }

    compress(source,divider,format);

    return 0;
}
