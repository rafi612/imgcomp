#!/bin/sh
cd ..
chmod +x compile.sh
sh -c ./compile.sh

cp imgcomp installer/imgcomp-deb/usr/bin/
cp imgcomp installer/imgcomp-targz/usr/bin/
cd installer

cd imgcomp-targz
echo "#!/bin/bash" > install.sh
echo "cp usr/bin/imgcomp /usr/bin/" >> install.sh
chmod +x install.sh
cd ..

tar -zcvf imgcomp.tar.gz imgcomp-targz
dpkg-deb --build imgcomp-deb
