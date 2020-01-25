CC= gcc
FLAGS= -Wall -g -fPIC


all: frequency
frequency: Trie.o
		$(CC) $(FLAGS) -o frequency Trie.o -lm
Trie.o: Trie.c Trie.h
		$(CC) $(FLAGS) -c Trie.c

.PHONY: clean all

clean:
		rm -f *.o frequency