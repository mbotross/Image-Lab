######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Fall 2018
#
# 10/30/18 Mihnea Chirila: updated for EECS22 Assignment 3 Fall 2018
#
######################################################################


# design names
DESIGN = PhotoLab PhotoLabTest

#libs
LIBS   = libFilter.a

CC     = gcc
DEBUG  = -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c -g
LFLAGS = -ansi -std=c99 -Wall -lm -g
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         edge.ppm \
         shuffle.ppm \
	 brightness.ppm \
         hmirror.ppm \
         hue.ppm \

all: PhotoLab PhotoLabTest


########### generate object files ###########

#target to generate FileIO.o
FileIO.o: FileIO.h FileIO.c Image.h Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c Image.h Constants.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c Image.h Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o


Image.o: Image.h Image.c
	$(CC) $(CFLAGS) Image.c -o Image.o
Test.o: Test.h Test.c Image.h DIPs.h Advanced.h FileIO.h Constants.h
	$(CC) $(CFLAGS) Test.c -o Test.o

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab_v3.c DIPs.h Test.h Advanced.h Image.h FileIO.h Constants.h
	$(CC) $(CFLAGS) PhotoLab_v3.c -o PhotoLab.o

#target to generate FileIO_DEBUG.o
PhotoLab_DEBUG.o: PhotoLab_v3.c  DIPs.h Test.h Advanced.h FileIO.h Image.h Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab_v3.c -o PhotoLab_DEBUG.o




########### generate library files ###########

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a


########### generate executables ###########

#target to generate PhotoLab
PhotoLab: PhotoLab.o Image.o Test.o  FileIO.o libFilter.a
	$(CC) $(LFLAGS) -g PhotoLab.o FileIO.o Image.o Test.o -L. -lFilter -o PhotoLab

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o Image.o Test.o FileIO.o libFilter.a
	$(CC) $(LFLAGS) -g PhotoLab_DEBUG.o Image.o FileIO.o Test.o -L. -lFilter -o PhotoLabTest
	

#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)

