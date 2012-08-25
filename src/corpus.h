#include <stdio.h>

#ifndef HEADER_CORPUS_GENERATOR
#define HEADER_CORPUS_GENERATOR

typedef struct
{
    int other;
    int seen;
} corpus_node;

typedef struct corpus_chain
{
    int value;
    int corpus_amount;
    int seen_total;
    corpus_node * corpus;
} corpus_chain;

typedef struct 
{
    int amount;
    corpus_chain * root;
} corpus_root;

corpus_root * generate_chain(FILE * value);

#endif
