corpus : builddir corpus.o corpus-main.o
	gcc build/corpus.o build/corpus-main.o  -o build/corpus

corpus.o : builddir
	gcc -Wall -c -o build/corpus.o src/corpus.c

corpus-main.o : builddir
	gcc -Wall -c -o build/corpus-main.o src/corpus-main.c

builddir :
	mkdir -p build

clean : 
	rm -Rf build
