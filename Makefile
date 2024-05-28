main: prog

prog: Main.o funkcijos.o 
	g++ -o prog Main.o funkcijos.o -O3
Main.o: Main.cpp funkcijos.h Vector.h
	g++ -c Main.cpp -o Main.o -O3
funkcijos.o: funkcijos.cpp funkcijos.h Vector.h
	g++ -c funkcijos.cpp -o funkcijos.o -O3

test: test_prog
	./test_prog
test_prog: tests.o funkcijos.o
	g++ -o test_prog tests.o funkcijos.o -O3
tests.o: tests.cpp funkcijos.h Vector.h
	g++ -c tests.cpp -o tests.o -O3 -Icatch2

clean:
	del *.o prog.exe test_prog.exe
.PHONY: main clean test
