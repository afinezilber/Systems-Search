#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ftw.h>
#include "traverse.h"
#include "tokens.h"
#include "index.h"

int traverse(const char *filename, const struct stat *status, int type) 
{
	char temp[1024];
	strcpy(temp, filename);
	if(type == FTW_NS){
		return 0;
	}
	if(type == FTW_F)
		tokenize(temp);
 
	if(type == FTW_D && strcmp(".", filename) != 0){
		
	}
	return 0;
}
