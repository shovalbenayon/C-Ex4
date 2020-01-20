#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h>

#define ALPHABET 26
#define ERROR -1

typedef struct TrieNode {
    char letter;
    long unsigned int wordsNum;
    struct TrieNode* children[ALPHABET];
    bool endWord;
    int sameWord;
} TrieNode;

int toIndex(char ch) {
    if ((int)ch >= 65 && (int)ch <= 90) return (int)ch - 65; // Upper case --> lower case --> index
    if ((int)ch >= 97 && (int)ch <= 122) return (int)ch - 97; // Lower case --> index
    return ERROR; // Invalid char
}

TrieNode* createTrieNode() {
    TrieNode* newNode = NULL;
    newNode = (TrieNode*)malloc(sizeof(TrieNode));

    if (newNode) {
        newNode->endWord = false;
        for (int i = 0; i < ALPHABET; i++)
            newNode->children[i] = NULL;
    }

    return newNode;
}

void insert(TrieNode* trieRoot, const char *anyWord) {
    int wordLength = strlen(anyWord);
    TrieNode* trieNode = trieRoot;

    for (int i = 0; i < wordLength; i++) {
        int indexNum = toIndex(anyWord[i]);
        if (indexNum != ERROR) {
            if (i == 0) trieRoot->wordsNum++; // Total amount of inserted words
            if (trieNode->children[indexNum] == NULL) {
                trieNode->children[indexNum] = createTrieNode();
                trieNode->children[indexNum]->letter = anyWord[i];
            } // Create new TrieNode

            trieNode = trieNode->children[indexNum];
            if (i == 0) trieNode->wordsNum++; // Increment anyWord's prefix wordsNum
        } // Invalid index will not be considered
    }

    if (trieNode->endWord) trieNode->sameWord++; // Check anyWord's existence
    else {
        trieNode->endWord = true;
        trieNode->sameWord = 1;
    }
}

void Lexicographic(const TrieNode* trieRoot, char outWord[], int indexNum, bool toReverse) {
    if (trieRoot->endWord) { // Leaf
        outWord[indexNum] = '\0';
        printf("%s\t %d\n", outWord, trieRoot->sameWord);
    }
    
    int rIndex; // Depends on the bool variable
    for (int i = 0; i < ALPHABET; i++) {
        if (toReverse) rIndex = ALPHABET - 1 - i; // Reverse
        else rIndex = i; // Forward
        if (trieRoot->children[rIndex] != NULL) {
            outWord[indexNum] = rIndex + 'a';
            Lexicographic(trieRoot->children[rIndex], outWord, indexNum + 1, toReverse);
        }
    }
}

void print(const TrieNode* trieRoot, bool toReverse) {
    char outWord[256];
    Lexicographic(trieRoot, outWord, 0, toReverse);
}

void freeMemo(TrieNode* trieRoot) { // Free memory allocation
    for (int i = 0; i < ALPHABET; i++)
        if (trieRoot->children[i] != NULL)
            freeMemo(trieRoot->children[i]);
        
    free(trieRoot);
}

int main(int argc, char **argv) {
    TrieNode* trieRoot = createTrieNode(); // Create an empty Trie root
    bool toReverse = false;
    if (argc == 2) if (!strncmp(argv[1], "r", 1)) toReverse = true;
    
    char anyWord[256];
    while (scanf("%s", anyWord) != EOF) insert(trieRoot, anyWord);

    print(trieRoot, toReverse);
    freeMemo(trieRoot);
    return 0;
}