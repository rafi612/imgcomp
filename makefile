all:
	g++ launch.cpp -o launch.o
	cd bin && jar cvfe imgcomp.jar com.main.ImageCompressorMain *
	mv bin/imgcomp.jar .
	cat launch.o imgcomp.jar > imgcomp
	chmod +x imgcomp
win:
	g++ launch.cpp -o launch.o
	cd bin && jar cvfe imgcomp.jar com.main.ImageCompressorMain *
	move bin/imgcomp.jar .
	type launch.o imgcomp.jar > imgcomp.exe
launch: launch.cpp
	g++ -c launch.cpp -o launch.o
java:
	cd bin && jar cvfe imgcomp.jar com.main.ImageCompressorMain *
	mv bin/imgcomp.jar .
cat:
	cat launch.o imgcomp.jar > imgcomp
clean:
	rm launch.o
	rm imgcomp.jar
chmod:
	chmod +x imgcomp
install:
	sudo mv imgcomp /usr/bin/
	sudo chmod +x /usr/bin/imgcomp
uninstall:
	sudo rm /usr/bin/imgcomp
