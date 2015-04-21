#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "search.h"
#include "uthash.h"
#include <errno.h>

int file_gets(char * filename, char ** res)
{
	FILE * fp = fopen (filename, "rb");
	int s;
	if (fp == NULL)
	return -1;
	fseek (fp, 0, SEEK_END);
	s = ftell (fp);
	fseek (fp, 0, SEEK_SET);
	*res = malloc (s + 1);
	memset (*res, '\0', s+ 1);
	if (s != fread (*res, sizeof (char), s, fp))
	return -2;
	fclose (fp);
	return s;
}

void stokenizer(char* invertedIndex )
{
	const char list1[] = "<list>";
	const char list2[] = "</list>";
    const char delim[] = " \n";
	int rf = 0;
 //   const char filename[256];
 //   FILE *input_file = fopen(invertedIndex, "r" );
    char *wholefile, *endfile, *file;
    char currkey[100];
	memset(currkey, '\0', sizeof(currkey));

//   if(input_file == NULL)
//        fprintf( stderr, "Unable to open file %s\n", filename );
   
    rf = file_gets(invertedIndex, &wholefile);
	file = strtok(wholefile, delim);
	while(file != NULL)
    {
		if(strcmp(list2, file) == 0)
		{
			file = strtok(NULL, delim);
			if(file == NULL)
				break;
			continue;
		}
		
		if(strcmp(list1, file) == 0)
		{						
			file = strtok(NULL, delim);
			strcpy(currkey, file);
			file = strtok(NULL, delim);
			strtok(NULL, delim);
		}
						
		indexer(file, currkey);
        file = strtok( NULL, delim );
        if(strcmp(list2, file) != 0)
        {
			endfile = strtok( NULL, delim);
			if(endfile == NULL)
				break;
		}
           
     }
}
/*        if(ferror(input_file) )
        {
            perror( "The following error occurred" );
        }

        fclose(input_file );
}*/
