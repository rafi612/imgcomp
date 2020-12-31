#!/bin/sh
cd ..
chmod +x compile.sh
sh -c ./compile.sh

cp imgcomp installer/imgcomp-deb/usr/bin/
cp imgcomp installer/imgcomp-targz/usr/bin/
cd installer

cd imgcomp-targz
echo "#!/bin/bash" > install.sh
echo "echo Imgcomp request java to working. Install it before install imgcomp" >> install.sh
echo "Press [ENTER] to install imgcomp" >> install.sh
echo "read -p \"$*\"" >> install.sh
echo "cp usr/bin/imgcomp /usr/bin/" >> install.sh
chmod +x install.sh
cd ..

tar -zcvf imgcomp.tar.gz imgcomp-targz
dpkg-deb --build imgcomp-deb

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
