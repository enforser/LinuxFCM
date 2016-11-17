install: install-bin/install.o program.o
	g++  -o install install-bin/install.o
	g++  -o ex program.o

intall/install.o: install-bin/install.cpp install-bin/install.h
	g++  -c install-bin/install.cpp

program.o: program.cpp
	g++  -c program.cpp

clean:
	rm -f install-bin/install.o program.o install ex
