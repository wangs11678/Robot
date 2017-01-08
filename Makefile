CC = g++

CXXFLAGS = $(shell pkg-config --cflags opencv)
LDLIBS = $(shell pkg-config --libs opencv)

objects = main.cpp socket_server.cpp serial_send.cpp sift_bow_svm.cpp clientVedio.cpp

bow : $(objects)
	$(CC) -o bow $(objects) $(CXXFLAGS) $(LDLIBS) -lpthread

clean:
	/bin/rm -f bow *.o

clean-all: clean
	/bin/rm -f *~ 
