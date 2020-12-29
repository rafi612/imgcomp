#!/bin/bash

cd bin
jar cvfe imgcomp.jar com.main.ImageCompressorMain *
cd ..
mv bin/imgcomp.jar .

g++ launch.cpp -o launch.o

cat launch.o imgcomp.jar > imgcomp
