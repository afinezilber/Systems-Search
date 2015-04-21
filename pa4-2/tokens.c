#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include <errno.h> 
#include "index.h"
#include "tokens.h"  
#define BUFFER_SIZE 2048


void tokenize( char* readFile)
{
    const char delim[] = "!@#$%^&*()_+ `~';/.,<>?|:[]{}\\=-\"\n";
    const char filename[256];
    FILE *input_file = fopen(readFile, "r" );
    char buffer[BUFFER_SIZE];
    char *last_token;
    int i;
    
    if(input_file == NULL)
    {
        fprintf( stderr, "Unable to open file %s\n", filename );
    }
    
    else
    {	
                 
        while(fgets(buffer, BUFFER_SIZE, input_file) != NULL )
        {

           last_token = strtok(buffer, delim);
           while(last_token != NULL)
            {			
				for(i = 0; i <= strlen(last_token); i++)
				{
					if(last_token[i] >= 65 && last_token[i] < 97)
					last_token[i] = last_token[i] + 32;
				}
				
				indexer(last_token, readFile);
                last_token = strtok( NULL, delim);
            }
        }
       // if(ferror(input_file) )
           // perror( "The following error occurred" );

        fclose(input_file );
    }
}


