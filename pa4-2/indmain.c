#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>
#include "index.h"
#include "tokens.h"
#include "traverse.h"
#include "uthash.h"

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("The number of arguments is invalid!\n");
        printf("Try again using: ./index <Filename to Write to> <Directory Path or Filename>\n");
        return 0;
    }
    
    FILE *fp = fopen(argv[1], "r");
    if(fp)
    {
			printf("The file inputted already exists; Override? Y/N\n");
			if(tolower(getchar()) == 'n')
			{
				printf("File will not be overwritten. Program will exit.");
				return 0;
            }

    }
    
	ftw(argv[2], traverse, 1);
    
    hashsort();
	print_disc(argv[1]);
	free_delete();
   
    return 0;
}
