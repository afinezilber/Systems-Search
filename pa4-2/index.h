#ifndef INDEX_H
#define INDEX_H
#include "uthash.h"

struct fileRecord {
	char file[124];
	int count;
	UT_hash_handle hh;
};

struct tokenRecord {
    char token[124];
    int count;
    UT_hash_handle hh;
    struct fileRecord* files;
}; 
void print_disc(char *filename);

void indexer(char* token, char* filename);

int sort_by_token(struct tokenRecord *a, struct tokenRecord *b);

void hashsort();

void free_delete();
#endif
