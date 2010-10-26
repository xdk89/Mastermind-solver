# makefile -- this is a comment line, ignored by make utility 

a.out: main.o imageloader.o
	g++ -o a.out main.o imageloader.o -I/usr/X11R6/include/ -L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU

main.o: main.cpp 
	g++ -o main.o -c main.cpp

imageloader.o: imageloader.h imageloader.cpp
	g++ -o imageloader.o imageloader.cpp -c

clean:
	rm *.o a.out 
