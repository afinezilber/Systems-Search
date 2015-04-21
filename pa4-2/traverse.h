#ifndef TRAVERSE_H
#define TRAVERSE_H
#include "index.h"
#include <ftw.h>
#include "tokens.h"

int traverse(const char *filename, const struct stat *status, int type);
#endif
