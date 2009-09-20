CC = gcc
LIBS = -lm

all:
	$(CC) -o daisy daisy.c cspeak.c $(LIBS)
	$(CC) -o reciter reciter.c cspeak.c $(LIBS)

clean:
	rm daisy reciter
