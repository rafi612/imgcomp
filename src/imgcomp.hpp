#ifndef IMGCOMP_H
#define IMGCOMP_H

#include <string>

using namespace std;

enum
{
    PNG = 0,
    JPG = 1,
    BMP = 2
};

unsigned char * load_image(string srcpath,int* w,int* h,int* comp,const int destformat);
unsigned char* compress_image(unsigned char* pixels,int w,int h,int comp,double divider,const int format,int* out_w,int* out_h,int* dest_chan);
void write_image(string destpath,unsigned char* output_pixels,int out_w,int out_h,int comp,const int format);

#endif
