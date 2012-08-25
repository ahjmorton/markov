all : corpus rand-markov

corpus : builddir corpus.o corpus-main.o
	gcc build/corpus.o build/corpus-main.o  -o build/corpus

corpus.o : builddir
	gcc -Wall -c -o build/corpus.o src/corpus.c

corpus-main.o : builddir
	gcc -Wall -c -o build/corpus-main.o src/corpus-main.c

builddir :
	mkdir -p build

rand-markov : builddir rand-markov.o
	gcc build/rand-markov.o -o build/rand-markov

rand-markov.o : builddir
	gcc -Wall -c -o build/rand-markov.o src/rand-markov.c

clean : 
	rm -Rf build

