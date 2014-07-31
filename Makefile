# Simple Makefile for jwHash. To build your program, just run make:
#    $ make

jwHash: jwHash.c
	g++ -O3 -o $@ $<
