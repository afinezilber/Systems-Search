#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "uthash.h"
#include "search.h"
#include "stokenizer.h"


int main(int argc, char* argv[])
{
//    if(argc != 1)
 //   {
 //       printf("The number of arguments is invalid!\n");
 //       printf("Try again using: ./search <Indexed File to Search>\n");
//        return 0;
//    }
    
    char *input;
    char *last_token;
    int count = 0;
    
    stokenizer(argv[1]);   
    input = readline("Please insert type of search followed by the tokens you want to search or hit q to quit: ");
       while(input[0] != 'q')
       { 
		   last_token = strtok(input, " ");
       
			if(strcmp(last_token, "sa") == 0)
			{
				char ** array  = NULL;
				int n_spaces = 0;
				last_token = strtok(NULL, " ");
				
				while(last_token)
				{
				  array = realloc (array, sizeof (char*) * ++n_spaces);

				  if (array == NULL)
					exit (-1); 

				  array[n_spaces-1] = last_token;

				  last_token = strtok (NULL, " ");
				  count = count + 1;
				}

				array = realloc (array, sizeof (char*) * (n_spaces+1));
				array[n_spaces] = 0;
				//printf("\n%s%s%s%s\n", array[0], array[1], array[2], array[3] );
                saSearch(array, count);
				free(array);
		    }
		    else if(strcmp(last_token, "so") == 0)
		    {
			 	last_token = strtok(NULL, " ");
			 	while(last_token)
				{
					soSearch(last_token);
					last_token = strtok(NULL, " ");
				}
				printSo();
			}
		 input = readline("\nPlease insert type of search followed by the tokens you want to search: "); 	
		}
		  	   
	free_delete();
    return 0;
}


