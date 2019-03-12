CC=g++
CFLAGS=-I. -Wall
DEPS = freqwo.cpp
OBJ = libmldevw.o word.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

freqwo: $(OBJ)
	$(CC) -o $@ freqwo.cpp $^ $(CFLAGS)
