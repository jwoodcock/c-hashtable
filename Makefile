# Simple Makefile for HashBrowns. To build your program, just run make:
#    $ make

jwHash: HashBrowns.c
	g++ -O3 -o $@ $<

benchmark: HashBrowns.c benchmark.c
	g++ -O3 -o benchmark benchmark.c
