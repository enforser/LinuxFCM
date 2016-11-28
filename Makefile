install: install-bin/install.o scripts/program.o scripts/pack.o scripts/unpack.o scripts/convert.o scripts/uninstall.o
	g++  -o install install-bin/install.o
	g++  -o scripts/ex scripts/program.o
	g++  -o scripts/pack scripts/pack.o
	g++  -o scripts/unpack scripts/unpack.o
	g++  -o scripts/convert scripts/convert.o
	g++  -o scripts/uninstall scripts/uninstall.o

install.o: install-bin/install.cpp install-bin/install.h
	g++  -c install-bin/install.cpp

program.o: scripts/program.cpp
	g++  -c scripts/program.cpp

pack.o: scripts/pack.cpp
	g++  -c scripts/pack.cpp

unpack.o: scripts/unpack.cpp
	g++ -c scripts/unpack.cpp

convert.o: scripts/convert.cpp
	g++ -c scripts/convert.cpp

uninstall.o: scripts/uninstall.cpp
	g++ -c scripts/uninstall.cpp

clean:
	rm -f install-bin/install.o scripts/*.o install scripts/ex

uninstall:
	./scripts/uninstall
