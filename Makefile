# Makefile for OpenGL/GLUT programs.

# Author: John M. Weiss, Ph.D.
# Written Fall 2014 for CSC433/533 Computer Graphics.

# Usage:  make target1 target2 ...

#-----------------------------------------------------------------------

# GNU C/C++ compiler and linker:
CC = gcc
CXX = g++
LINK = g++

# Turn on optimization and warnings (add -g for debugging with gdb):
# CPPFLAGS = 		# preprocessor flags
CFLAGS = -O -Wall -g
CXXFLAGS = -O -Wall -g -std=c++11

# OpenGL/Mesa libraries for Linux:
GL_LIBS = -lglut -lGLU -lGL -lm

#-----------------------------------------------------------------------

# MAKE allows the use of "wildcards", to make writing compilation instructions
# a bit easier. GNU make uses $@ for the target and $^ for the dependencies.

all:    solar_system

# specific targets

# typical target entry, builds "myprog" from file1.cpp, file2.cpp, file3.cpp
myprog:	file1.o file2.o file3.o
	$(LINK) -o $@ $^ $(GL_LIBS)

solar_system:	solar_system.o glut_callback_functions.o keypresses.o bmp_read.o menu.o
	$(LINK) -o $@ $^ $(GL_LIBS)

# generic C and C++ targets for OpenGL programs consisting of only one file
# type "make filename" (no extension) to build
.c:
	$(CC) -o $@ $@.c $(GL_LIBS)

.cpp:
	$(CXX) -o $@ $@.cpp $(GL_LIBS)

# utility targets
clean:
	rm solar_system -f *.o *~ core
