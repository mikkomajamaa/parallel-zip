all: pzip punzip
pzip: pzip.c
	gcc -pthread -o pzip pzip.c -Wall
punzip: punzip.c
	gcc -pthread -o punzip punzip.c -Wall
