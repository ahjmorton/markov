#include <stdio.h>
#include "corpus-data.h"

#ifndef HEADER_CORPUS_GENERATOR
#define HEADER_CORPUS_GENERATOR

corpus_root * generate_chain(FILE * value);

void free_chain(corpus_root *);

#endif
