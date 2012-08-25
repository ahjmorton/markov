#ifndef HEADER_CORPUS_DATA_GENERATOR
#define HEADER_CORPUS_DATA_GENERATOR

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

#endif
