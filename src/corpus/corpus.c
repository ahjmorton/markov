/*
This file is part of markov.

markov is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

markov is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with markov.  If not, see <http://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>

#include "corpus.h"

typedef struct corpus_index_value {
    int value;
    struct corpus_index_value * next;
    corpus_node * node;
} corpus_index_value;

typedef struct corpus_index_key {
    int key;
    corpus_chain * chain;
    struct corpus_index_key * next;

    unsigned int valueCount;
    unsigned int memSpaces;
    corpus_index_value * values;

} corpus_index_key;

typedef struct {
    unsigned int keyCount;
    unsigned int memSpaces;
    corpus_index_key * keys;   
} corpus_index;

#define INITIAL_INDEX_SIZE 64

static corpus_index * createIndex() {
    return NULL;
}

static void free_index(corpus_index * index) {

}

static corpus_node * find_node(int amount, corpus_node * chain, int other) {
    int i;
    for(i = 0; i < amount; i++) {
        corpus_node * search = chain + i;
        if(search->other == other) {
            return search;
        }
    }
    return NULL;
}

static corpus_chain * find_chain(int amount, corpus_chain * chain, int value) {
    int i;
    for(i = 0; i < amount; i++) {
       corpus_chain * search = chain + i;
       if(search->value == value) {
           return search;
       }
    }
    return NULL;
}

static void add_pair(corpus_root * root, int key, int value) {
    corpus_chain * chain = find_chain(root->amount, root->root, key);
    if(chain == NULL) {
        ++(root->amount);
        root->root = (corpus_chain *)realloc(root->root, root->amount * sizeof(corpus_chain));
        chain = root->root + (root->amount - 1);
        chain->value = key;
        chain->corpus_amount = 0;
        chain->seen_total = 0;
        chain->corpus = NULL;
    }
    corpus_node * node = find_node(chain->corpus_amount, chain->corpus, value);
    if(node == NULL) {
        ++(chain->corpus_amount);
        chain->corpus = (corpus_node *)realloc(chain->corpus, chain->corpus_amount * sizeof(corpus_node));
        node = chain->corpus + (chain->corpus_amount - 1);
        node->other = value;
        node->seen = 0;
          
    }
    chain->seen_total = chain->seen_total + 1;
    node->seen = node->seen + 1;
}

corpus_root * generate_chain(FILE * value)
{
    int previous = getc(value);
    int next;
    int total = 0;
    if(previous == EOF) {
        return NULL;
    }
    corpus_root * chain = (corpus_root *)calloc(1, sizeof(corpus_root));
    while((next = getc(value)) != EOF) {
       add_pair(chain, previous, next);
       previous = next;
    }
    return chain;
}

void free_chain(corpus_root * root) {
    int i;
    for(i = 0; i < root->amount; i++) {
       free((root->root + i)->corpus);
    }
    free(root->root);
    free(root);
}
