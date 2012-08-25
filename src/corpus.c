#include <stdio.h>
#include <stdlib.h>

#include "corpus.h"

static struct pairs 
{
    int first;
    int second;
}

static pairs * make_pair(int first, int second) {
    pairs * pair = (pairs *)malloc(sizeof(pairs));
    pair->first = first;
    pair->second = second;
    return pair;
}

static corpus_node * make_node(int other) {
    corpus_node * node = (corpus_node *)malloc(sizeof(corpus_node));
    node->other = other;
    node->seen = 1;
    return node;
}

static corpus_chain * make_chain_node(int value) {
    corpus_chain * chain = (corphus_chain)calloc(1, sizeof(corpus_chain));
    chain->value = value;
    chain->seen_total = 1;
    return chain;
}

static corpus_node * find_node(corpus_chain * chain, int other) {
    corpus_node * search = chain->corpus;
    int i ;
    for(i = 0; i < chain->corpus_amount && search->other != other; i++) {
        ++search;
    }
    if(search == NULL) {
        corpus_node * node = make_node(other);
 
    }
    return search;
}

static corpus_chain * find_chain(corpus_chain * root, int value) {
    corpus_chain * search = root;
    while(search->next != NULL && search->value != value) {
        search = search->next;
    }
    // The next item is null and the value is not the one
    // we want, so create a new node, append it to the chain
    // and return it
    if(search->next == NULL && search->value != value) {
        corpus_chain * next = make_chain_node(value);
        search->next = next;
        search = next;
    }
    return search;
}

static corpus_chain * make_chain(int count, pairs * both) {
   int i;
   if(count == 0) {
       return NULL;
   }
   corpus_chain * root = make_chain_node(both->first);
   root->corpus = make_node(both->second);
   root->amount = 1;
   for(i = 1; i < count; ++i) {
       pairs * current = both + i;
       corpus_chain * node = find_chain(root, current->first);
   }
   return NULL;
}

corpus_chain * generate_chain(int count, FILE * values)
{
    return NULL;
}

