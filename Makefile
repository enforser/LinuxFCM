install: install-bin/install.o scripts/program.o
	g++  -o install install-bin/install.o
	g++  -o scripts/ex scripts/program.o

install.o: install-bin/install.cpp install-bin/install.h
	g++  -c install-bin/install.cpp

program.o: scripts/program.cpp
	g++  -c scripts/program.cpp

clean:
	rm -f install-bin/install.o scripts/program.o install scripts/ex
