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
    struct corpus_chain * next;
} corpus_chain;

corpus_chain * generate_chain(int count, FILE * value);

#endif
