#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb/stb_image.h>
#include <stb/stb_image_resize.h>
#include <stb/stb_image_write.h>

#include <iostream>

#include "imgcomp.hpp"
#include "util.hpp"

using namespace std;

unsigned char *load_image(std::string srcpath,int* w,int* h,int* comp,const int dest_format)
{
    int dest_chan = dest_format == JPG ? STBI_rgb : STBI_rgb_alpha;

    return stbi_load(srcpath.c_str(),w,h,comp,dest_chan);
}

unsigned char* compress_image(unsigned char* pixels,int w,int h,int comp,double divider,const int format,int* out_w,int* out_h,int* dest_chan)
{
    *out_w = (int)(w / divider);
    *out_h = (int)(h / divider);

    *dest_chan = format == JPG ? STBI_rgb : STBI_rgb_alpha;

    unsigned char* output_pixels = (unsigned char*) malloc((*out_w) * (*out_h) * (*dest_chan));

    stbir_resize_uint8(pixels,w,h,0,output_pixels,*out_w,*out_h,0,*dest_chan);
    stbi_image_free(pixels);

    return output_pixels;
}

void write_image(string destpath,unsigned char* output_pixels,int out_w,int out_h,int comp,const int format)
{
    switch (format)
    {
    case JPG:
        stbi_write_jpg(destpath.c_str(),out_w,out_h,STBI_rgb,output_pixels,100);
        break;
    case PNG:
        stbi_write_png(destpath.c_str(),out_w,out_h,STBI_rgb_alpha,output_pixels,0);
        break;
    case BMP:
        stbi_write_bmp(destpath.c_str(),out_w,out_h,comp,output_pixels);
        break;
    }

    stbi_image_free(output_pixels);
}
