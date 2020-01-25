#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>
#include "Trie.h"

#define ALPHABET 26
#define EMPTY -2
int len = 0;

int toIndex(char ch) {
    if ((int)ch >= 65 && (int)ch <= 90)
        return (int)ch - 65; // Upper case to lower case to index
    if ((int)ch >= 97 && (int)ch <= 122)
        return (int)ch - 97; // Lower case to index
    return -1; // Invalid char
}

bool ifNotLetter(char ch) {
    if ((int)ch >= 0 && (int)ch <= 32) return true;
    return false;
}

TrieTree* createTrie() {
    TrieTree* nTrie = NULL;
    nTrie = (TrieTree*)malloc(sizeof(TrieTree));

    if (nTrie) {
        nTrie->endWord = false;
        for (int i = 0; i < ALPHABET; i++)
            nTrie->children[i] = NULL;
    }

    return nTrie;
}

TrieTree* insert(TrieTree* root, const char letter, int index) {
    if (root->children[index] == NULL) {
        root->children[index] = createTrie();
        root->children[index]->letter = letter;
    } // Create new TrieTree

    root = root->children[index];
    return root;
}

void Lexicographic(TrieTree* root, char word[len], int num, bool reverse) {
    if (root->endWord && !reverse) { // Forward
        word[num] = '\0';
        if (root->letter != EMPTY)
            printf("%s\t%d\n", word, root->equalWord);
    }
    
    int indexr; // Depends on the bool variable
    for (int i = 0; i < ALPHABET; i++) {
        if (reverse)
            indexr = ALPHABET - 1 - i; // Reverse
        else indexr = i; // Forward

        if (root->children[indexr] != NULL) {
            word[num] = indexr + 'a';
            Lexicographic(root->children[indexr], word, num + 1, reverse);
        }
    }
    
    if (root->endWord && reverse) { // Reverse
        word[num] = '\0';
        if (root->letter != EMPTY)
            printf("%s\t%d\n", word, root->equalWord);
    }
}

void print(TrieTree* trieRoot, bool toReverse) {
    char outWord[len];
    Lexicographic(trieRoot, outWord, 0, toReverse);
}

void freeMemory(TrieTree* root) { // Free memory allocation
    for (int i = 0; i < ALPHABET; i++)
        if (root->children[i] != NULL)
            freeMemory(root->children[i]);
        
    free(root);
}

int main(int argc, char** argv) {
    TrieTree* root = createTrie(); // Create an empty Trie root
    root->letter = EMPTY; // root contains no letters at all
    bool reverse = false;
    if (argc == 2)
	if (!strncmp(argv[1], "r", 1))
        reverse = true;

    char letter;
    int num;
    int leng = 0;

    TrieTree* node = root;
    while (scanf("%c", &letter) != EOF) {
        num = toIndex(letter);
        if (num >= 0 && num <= 25) {
            node = insert(node, letter, num);
            leng++;
            if (leng > len) len = leng;
        }

        else if (ifNotLetter(letter)) {
            if (node->endWord)
                node->equalWord++;
            else {
                node->endWord = true;
                node->equalWord = 1;
            }

            if (leng > 0)
                root->NumOfWords++;
            leng = 0;
            node = root;
        }
    }

    // Reached EOF before updating the last word end
    if (node->endWord) node->equalWord++;
    else {
        node->endWord = true;
        node->equalWord = 1;
    }

    print(root, reverse);
    freeMemory(root);
    return 0;
}
