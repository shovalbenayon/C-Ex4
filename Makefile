CC = gcc
FLAGS = -Wall -g -fPIC

all: frequency
frequency: Trie.c
	$(CC) $(FLAGS) Trie.c -o frequency

.PHONY: clean all

clean:
	rm -f *.o frequency
