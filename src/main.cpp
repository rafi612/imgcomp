#include <iostream>
#include <filesystem>

#include "util.h"
#include "imgcomp.h"

#define VERSION "0.1.1"

using namespace std;
namespace fs = std::filesystem;

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

void compress(string file,double divider,string format,bool keepfiles,bool names)
{
    cout << "Searching files..." << endl;

    vector<string> files;
    if (fs::is_directory(file)) get_files(&files,file);
    else files.push_back(file);

    size_t sizebefore = fs::file_size(file);

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
    uint64_t elapsedTime = 0;

    string filenameaddon = "-compress.";
    if (names) filenameaddon = ".";

    string out_path;

    for (int i = 0; i < files.size();i++)
	{
        percent = (int)((double)i / (double)files.size() * (double)100);
        elapsedTime = (timeSinceEpochMillisec() / 1000) - startTime;
        size_t allTimeForCompressing = (elapsedTime * files.size() / (compressedFiles + 1));
        size_t remainingTime = allTimeForCompressing - elapsedTime;

        if (!fs::is_directory(files[i]))
        {
            if (is_supported_image(files[i]))
            {
                cout << "Compressed: " << percent << "% Elapsed: " << elapsedTime << "s ETA: " << remainingTime << "s" << endl;
                
                //load
                int w,h,comp;
                unsigned char* image = load_image(files[i],&w,&h,&comp,get_format_id(format));

                //remove old file
                fs::remove(files[i]);
                
                //output path
                string output = remove_extension(files[i]) + filenameaddon + format;
                out_path = fs::is_directory(file) ? file : output;

                //resize
                int out_w, out_h, dest_chan;
                unsigned char* out_image = compress_image(image,w,h,comp,divider,get_format_id(format),&out_w,&out_h,&dest_chan);

                //write
                write_image(output,out_image,out_w,out_h,dest_chan,get_format_id(format));

                cout << "Compressed " << files[i] << " -> " << output << endl;
			    compressedFiles++;
            }
            else cout << "Skipped " << files[i] << endl;
        }
	}

    cout << endl << "Compression Complete!!!" << endl;
	cout << "Searching files..." << endl << endl;
	size_t sizeafter = fs::file_size(out_path);

	cout << "Total time:" << elapsedTime << "s" << endl;
	cout << "Size before:" << (sizebefore / 1000 / 1000) << "MB (" << sizebefore << " Bytes)" << endl;
	cout << "Size after:" << (sizeafter / 1000 / 1000) << "MB (" << sizeafter << " Bytes)" << endl;

	double ratio = (int)((double)sizeafter / (double)sizebefore * (double)100);
	cout << "Lossy compression ratio: " << ratio << "%" << endl;
}

int main(int argc, char *argv[])
{
    cout << "Image Compressor " << VERSION << endl;  

    bool keepfiles,names;
    string source;
    string format;
    double divider = 0;  

    string flags = argv[1];
    if (argc == 1)
    {
       help();
       return 0;
    }

    int move;
    if (argc >= 2)
    {
        if (flags.find("-") == 0) move = 0;
        else move = 1;

        source = argv[2- move];
		divider = atof(argv[3 - move]);
		format = argv[4 - move];

        if (divider == 0) divider = 1;
    }
	if (move == 0)
	{
		if(contains(flags,"k"))
			keepfiles = true;

		if(contains(flags,"n"))
			names = true;
	}

    if (contains(flags,"-help"))
       help();

    if (fs::exists(source))
    {
        cerr << "Error: " << source << " not exists" << endl;
        return -1;
    }

    compress(source,divider,format,keepfiles,names);

    return 0;
}
