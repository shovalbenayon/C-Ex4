//
// Created by shoval on 25.1.2020.
//

#include <stdbool.h>

#ifndef EX4_C_TRIE_H
#define EX4_C_TRIE_H
#define ALPHABET 26
#define ERROR -1
#define EMPTY -2

typedef struct TrieTree {
    char letter;
    long unsigned int NumOfWords;
    struct TrieTree* children[ALPHABET];
    bool endWord;
    int equalWord;
} TrieTree;

int toIndex(char ch);
bool ifNotLetter(char ch);
TrieTree* createTrie();
TrieTree* insert(TrieTree* root, const char letter, int index);
void Lexicographic(TrieTree* root, char word[], int num, bool reverse);
void print(TrieTree* trieRoot, bool toReverse);
void freeMemory(TrieTree* root);
#endif //EX4_C_TRIE_H
