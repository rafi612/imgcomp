#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <stb/stb_image.h>
#include <stb/stb_image_resize.h>
#include <stb/stb_image_write.h>

#include <iostream>

#include "imgcomp.h"
#include "util.h"

unsigned char *load_image(std::string srcpath,int* w,int* h,int* comp,const int format)
{
    int dest_chan = format == JPG ? STBI_rgb : STBI_rgb_alpha;

    return stbi_load(srcpath.c_str(),w,h,comp,dest_chan);
}

void print(unsigned char *xd)
{
    for (int i = 0;i < 10;i++)
        cout << (int)xd[i] << endl;
}

unsigned char* convert2channel(unsigned char* input,int w,int h,int dest_chan,int src_chan)
{
    unsigned char* ret = (unsigned char*)malloc(w * h * dest_chan);

    int j = 0;
    for(size_t i = 0 ; i < w * h * src_chan; ++i )
    {
        ret[j] = input[i];
        j++;
    }

    return ret;

}

void compress_image(unsigned char* pixels,int w,int h,int comp,std::string destpath,double divider,const int f)
{
    //print(pixels);
    int out_w = (int)(w / divider);
    int out_h = (int)(h / divider);

    int dest_chan = f == JPG ? STBI_rgb : STBI_rgb_alpha;

    unsigned char* output_pixels = (unsigned char*) malloc(out_w * out_h * dest_chan);

    stbir_resize_uint8(pixels,w,h,0,output_pixels,out_w,out_h,0,dest_chan);
    stbi_image_free(pixels);

    switch (f)
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
