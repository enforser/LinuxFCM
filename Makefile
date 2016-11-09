install: install.o program.o
	g++  -o install install.o
	g++  -o ex program.o

install.o: install.cpp install.h
	g++  -c install.cpp

program.o: program.cpp
	g++  -c program.cpp

clean:
	rm -f install.o program.o install ex
