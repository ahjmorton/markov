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
#include "corpus-data.h"
#include "corpus-index.h"

static void add_pair(corpus_root * root, corpus_index * index, int key, int value) {
    corpus_index_key * index_key = find_index_key(index, key);
    if(index_key == NULL) {
        ++(root->amount);
        root->root = (corpus_chain *)realloc(root->root, root->amount * sizeof(corpus_chain));
        unsigned long int new_chain_index = root->amount - 1;
        corpus_chain * new_chain = root->root + new_chain_index ;
        new_chain->value = key;
        new_chain->corpus_amount = 0;
        new_chain->seen_total = 0;
        new_chain->corpus = NULL;
        index_key = add_index_key(index, new_chain_index, key);
    }
    corpus_chain * chain = root->root + index_key->chain_index;
    corpus_index_value * index_value = find_index_value(index_key, value);
    if(index_value == NULL) {
        ++(chain->corpus_amount);
        chain->corpus = (corpus_node *)realloc(chain->corpus, chain->corpus_amount * sizeof(corpus_node));
        unsigned long int new_node_index = chain->corpus_amount - 1;
        corpus_node * new_node = chain->corpus + new_node_index;
        new_node->other = value;
        new_node->seen = 0;
        index_value = add_index_value(index_key, new_node_index, value);
    }
    corpus_node * node = chain->corpus + index_value->node_index;
    chain->seen_total = chain->seen_total + 1;
    node->seen = node->seen + 1;
}

static corpus_root * create_root() {
    corpus_root * root = (corpus_root *)malloc(sizeof(corpus_root));
    root->amount = 0;
    root->root = NULL; 
    return root;
}

chain_options * create_default_ops(void) {
    chain_options * options = (chain_options *)malloc(sizeof(chain_options));
    options->input = stdin;
    options->ignore = NULL;
    options->ignoreCount = 0;
    return options;
}

void free_options(chain_options * ops) {
    if(ops->ignore != NULL) {
        free(ops->ignore);
    }
    free(ops);
}

static int is_ignored(int value, int * ignored, int ignoreAmount) {
    int i;
    if(ignoreAmount == 0 || ignored == NULL) {
        return 0;
    }
    for(i = 0; i < ignoreAmount; i++) {
        if(value == ignored[i]) {
            return 1;
        }
    }
    return 0;
}

corpus_root * generate_chain(chain_options * opts) {
    FILE * value = opts->input;
    int previous = getc(value);
    int next;
    int total = 0;
    corpus_root * chain = create_root();
    corpus_index * index = create_index();
    if(previous == EOF) {
        return NULL;
    }
    while((next = getc(value)) != EOF) {
       if(!is_ignored(next, opts->ignore, opts->ignoreCount) &&
          !is_ignored(previous, opts->ignore, opts->ignoreCount)) {
           add_pair(chain, index, previous, next);
       }
       previous = next;
    }
    free_index(index);
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
