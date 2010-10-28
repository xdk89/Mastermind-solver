# makefile -- this is a comment line, ignored by make utility 

mastermind: main.o imageloader.o
	g++ -o mastermind main.o imageloader.o -I/usr/X11R6/include/ -L/usr/X11R6/lib -lX11 -lXi -lXmu -lglut -lGL -lGLU

main.o: main.cpp validator.h common.h 
	g++ -o main.o -c main.cpp

imageloader.o: imageloader.h imageloader.cpp
	g++ -o imageloader.o imageloader.cpp -c

clean:
	rm *.o mastermind *.log
