CC = gcc
SRCS = daisy.c cspeak.c
LIBS = -lm

all:
	$(CC) -o daisy $(SRCS) $(LIBS)

clean:
	rm daisy
