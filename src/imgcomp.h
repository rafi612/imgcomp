#ifndef IMGCOMP_H
#define IMGCOMP_H

#include <string>

const int PNG = 0;
const int JPG = 1;
const int BMP = 2;

unsigned char * load_image(std::string srcpath,int* w,int* h,int* comp,const int destformat);
void compress_image(unsigned char* pixels,int w,int h,int comp,std::string destpath,double divider,const int f);

#endif
