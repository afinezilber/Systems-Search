#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include <errno.h> 
#include "search.h"

#define BUFFER_SIZE 2048

struct tokenRecord *indexs = NULL;
struct saStruct *first = NULL;
struct soStruct *head = NULL;


int sort_by_token(struct tokenRecord *a, struct tokenRecord *b)
{
  return strcmp(a->token,b->token);
}

void hashsort()
{
    HASH_SORT(indexs, sort_by_token);
}

void printSo()
{
		struct soStruct *so;
		for(so=head; so != NULL; so=(struct soStruct*)(so->hh.next)) 
		{
			printf("%s\t", so->filename);
		}
}

void saSearch(char** tokes, int noe)
{
	struct saStruct *sa;
	struct tokenRecord *s, *t;
	struct fileRecord *f, *g;
	int i;
	for(i=0; i < noe; i++)
	{
		HASH_FIND_STR(indexs, tokes[i], s);
		
		if(!s)
		{
			printf("%s not in the inverted index file, therefore cannot be used with the SA option.\n", tokes[i]);
			return; //one of the tokens is not found in any of the files. Therefore cannot be SA
		}
	}
	
	for(i=0;i < noe; i++)	
	{
		
		HASH_FIND_STR(indexs, tokes[0] , s);
		if(s)
		{
			
			HASH_FIND_STR(indexs, tokes[i], t);
			if(t)
			{
				
				for(f=s->files; f!=NULL; f=(struct fileRecord*) (f->hh.next))
				{
					for(g=t->files; g!=NULL; g=(struct fileRecord*) (g->hh.next))
					{
						if(strcmp(g->file, f->file) == 0)		//Does this compare the two filenames from each token list in the hashtable?
						{
							
							HASH_FIND_STR(first, g->file, sa);	//If it does, check to see if that file is already in the hash table
							if(!sa)								//if its not in the hash_table, add it.
							{
								sa = (struct saStruct*)malloc(sizeof(struct saStruct));
								strncpy(sa->filename, g->file, 124);
								HASH_ADD_STR(first, filename, sa);
								sa->count = 1;
							}
							else
								sa->count = sa->count++;
						}
					}
				}
			} 
		}
	}
	for(sa = first; sa != NULL; sa=(struct saStruct*)(sa->hh.next))
	{
		if(sa->count == noe)
		{
			printf("%s\t", sa->filename);
		}
	}
	printf("\n");
}

void soSearch(char *tokes)
{
	struct tokenRecord *s;
	struct fileRecord *f;
	struct soStruct *so;
	
	HASH_FIND_STR(indexs, tokes, s);
	if(s)
	{
		for(f=s->files; f != NULL; f=(struct fileRecord*)(f->hh.next))
		{
			HASH_FIND_STR(head, f->file, so); //SHOULD THIS BE JUST f or f->file?
			if(!so)
			{							
				so = (struct soStruct*)malloc(sizeof(struct soStruct));
				strncpy(so->filename, f->file, 124);
				HASH_ADD_STR(head, filename, so);
			}
		}
	}
	else
		printf("No matches found\n");
}
				
		
	
void indexer(char* token, char* key)
{
	struct tokenRecord *s;
	struct fileRecord *f;
	
	HASH_FIND_STR(indexs, key, s);
	if(!s) { 
		s = (struct tokenRecord*)malloc(sizeof(struct tokenRecord));
		strncpy(s->token, key, 124);
		HASH_ADD_STR(indexs, token, s); 
		s->files = NULL;
	} 
	
	HASH_FIND_STR(s->files, token, f);
	if(!f)
	{
		f = (struct fileRecord*)malloc(sizeof(struct fileRecord));
		strncpy(f->file, token, 124);
		HASH_ADD_STR(s->files, file, f); 
	}

}

void free_delete() 
{
	struct tokenRecord *tmp, *user;
    struct saStruct *tmp1, *user1;
    struct soStruct *tmp2, *user2;
    HASH_ITER(hh, indexs, user, tmp)
    {
		HASH_DEL(indexs,user); /* delete it (users advances to next) */
		free(user);            /* free it */
	}
	HASH_ITER(hh, first, user1, tmp1)
	{
		HASH_DEL(first,user1); /* delete it (users1 advances to next) */
		free(user1);            /* free it */
	}
    HASH_ITER(hh, head, user2, tmp2) 
    {
		HASH_DEL(head,user2); /* delete it (users2 advances to next) */
		free(user2);            /* free it */
	}
}



