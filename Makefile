install: install-bin/install.o scripts/program.o
	g++  -o install install-bin/install.o
	g++  -o scripts/ex scripts/program.o

<<<<<<< HEAD
install/install.o: install-bin/install.cpp install-bin/install.h
	g++ -c install-bin/install.cpp
=======
install.o: install-bin/install.cpp install-bin/install.h
	g++  -c install-bin/install.cpp
>>>>>>> fd0c8e3826fbfd4eae489d872e8b734ea0ccfc44

program.o: scripts/program.cpp
	g++  -c scripts/program.cpp

clean:
	rm -f install-bin/install.o scripts/program.o install scripts/ex
