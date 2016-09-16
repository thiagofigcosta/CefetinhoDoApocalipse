FORMAT=.cpp
CC=g++
SRC=$(wildcard *$(FORMAT))
CLASSES=$(wildcard Classes/*$(FORMAT))
EXEC=TCG
CFLAGS=-w -Wall -std=c++11
LDFLAGS=-lglut -lGLU -lGL -lm -lopenal -lGLEW -lSOIL

clean:
	rm -rf *.o $(EXEC)

all:
	$(CC) $(SRC) $(CLASSES) -o $(EXEC) $(CFLAGS) $(LDFLAGS)

run: all
	./$(EXEC)
