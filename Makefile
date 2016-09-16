FORMAT=.cpp
CC=g++
SRC=$(wildcard *$(FORMAT))
CLASSES=$(wildcard Classes/*$(FORMAT))
LIBS=$(wildcard Libs/*$(FORMAT))
EXEC=Bin/TCG
CFLAGS=-w -Wall -std=c++11
LDFLAGS=-lglut -lGLU -lGL -lm -lopenal -lGLEW -lSOIL

clean:
	rm -rf *.o $(EXEC)

all:
	$(CC) $(SRC) $(CLASSES) $(LIBS) -o $(EXEC) $(CFLAGS) $(LDFLAGS)

run: all
	./$(EXEC)
