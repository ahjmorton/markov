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

#include <stdlib.h>
#include <string.h>

#include "corpus-index.h"

#define INITIAL_MEM_SPACES 32

corpus_index_value * add_index_value(corpus_index_key * key, corpus_node * value){
    return NULL;
}

corpus_index_value * find_index_value(corpus_index_key * key, int value){
    return NULL;
}

corpus_index_key * add_index_key(corpus_index * index, corpus_chain * chain){
    return NULL;
}

corpus_index_key * find_index_key(corpus_index * index, int key){
    return NULL;
}

corpus_index * create_index(void){
    int i;
    size_t bucket_size = INITIAL_MEM_SPACES * sizeof(corpus_index_key *);

    corpus_index * index = (corpus_index *)malloc(sizeof(corpus_index));
    index->keys = (corpus_index_key **)malloc(bucket_size);
    for(i = 0; i < INITIAL_MEM_SPACES; i++) {
        *(index->keys + i) = NULL;
    }
    index->mem_spaces = INITIAL_MEM_SPACES;
    index->key_count = 0;

    return index;
}

static void free_index_value(corpus_index_value * value) {
    if(value != NULL) {
        free_index_value(value->next);
        free(value);
    }
}

static void free_index_key(corpus_index_key * key) {
    int i;
    if(key != NULL) {
        free_index_key(key->next);
        for(i = 0; i < key->mem_spaces; i++) {
            free_index_value(*(key->values + i));
        }
        free(key->values);
        free(key);
    }
}

void free_index(corpus_index * index){
    int i;
    for(i = 0; i < index->mem_spaces; i++) {
        free_index_key(*(index->keys + i));
    }
    free(index->keys);
    free(index);
}
