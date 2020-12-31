#!/bin/sh
#creating installer folders
cd imgcomp-deb
mkdir usr
cd usr
mkdir bin
cd ..
cd ..
cd imgcomp-targz
mkdir usr
cd usr
mkdir bin
cd ..
cd ..
#compiling
cd ..
chmod +x compile.sh
sh -c ./compile.sh
#copying
cp imgcomp installer/imgcomp-deb/usr/bin/
cp imgcomp installer/imgcomp-targz/usr/bin/
cd installer
#chmod
cd imgcomp-targz
chmod +x install.sh
cd ..
#packing
tar -zcvf imgcomp.tar.gz imgcomp-targz
dpkg-deb --build imgcomp-deb
#deleting
cd imgcomp-deb/usr/bin
rm imgcomp
cd ..
cd ..
cd ..
cd imgcomp-targz/usr/bin
rm imgcomp
cd ..
cd ..
cd ..
rm imgcomp-targz/install.sh
