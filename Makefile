# Simple Makefile for jwHash. To build your program, just run make:
#    $ make

jwHash: jwHash.c
	g++ -O3 -o $@ $<

benchmark: jwHash.c benchmark.c
	g++ -O3 -o benchmark benchmark.c
