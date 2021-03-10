#!/bin/sh

echo =============================
echo "To compile imgcomp you request:"
echo jdk,g++
echo =============================
javac -d bin $(find ./src/* | grep .java)

cd bin
jar cvfe imgcomp.jar com.main.ImageCompressorMain *
cd ..
mv bin/imgcomp.jar .

g++ launch.cpp -o launch.o

cat launch.o imgcomp.jar > imgcomp
rm launch.o
rm imgcomp.jar
chmod +x imgcomp
