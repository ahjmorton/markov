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

#define INITIAL_INDEX_BUCKETS 32
#define INITIAL_KEY_BUCKETS 32

corpus_index_value * add_index_value(corpus_index_key * key, corpus_node * value){
    int hash = value->other % key->mem_spaces;
    corpus_index_value * bucket;
    corpus_index_value ** bucket_cell = (key->values + hash);
    while(*bucket_cell != NULL) {
        bucket_cell = &((*bucket_cell)->next);
    }
    (*bucket_cell) = (corpus_index_value *)calloc(1, sizeof(corpus_index_value));
    bucket = (*bucket_cell);
    bucket->next = NULL;
    bucket->node = value;
    bucket->value = value->other;
    return bucket;
}

corpus_index_value * find_index_value(corpus_index_key * key, int value){
    int hash = value % key->mem_spaces;
    corpus_index_value * bucket = *(key->values + hash);
    while(bucket != NULL && bucket->value != value) {
        bucket = bucket->next;
    }
    return bucket;

}

corpus_index_key * add_index_key(corpus_index * index, corpus_chain * chain){
    int i;
    int hash = chain->value % index->mem_spaces;
    corpus_index_key * bucket;
    corpus_index_key ** bucket_cell = (index->keys + hash);
    while(*bucket_cell != NULL) {
        bucket_cell = &((*bucket_cell)->next);
    }
    (*bucket_cell) = (corpus_index_key *)calloc(1, sizeof(corpus_index_key));
    bucket = (*bucket_cell);
    bucket->next = NULL;
    bucket->chain = chain;
    bucket->key = chain->value;
    bucket->value_count = 0;
    bucket->values = (corpus_index_value **)malloc(INITIAL_KEY_BUCKETS * sizeof(corpus_index_value *));
    for(i = 0; i < INITIAL_KEY_BUCKETS; i++) {
        *(bucket->values + i) = NULL;
    }
    bucket->mem_spaces = INITIAL_KEY_BUCKETS;
    return bucket;
}

corpus_index_key * find_index_key(corpus_index * index, int key){
    int hash = key % index->mem_spaces;
    corpus_index_key * bucket = *(index->keys + hash);
    while(bucket != NULL && bucket->key != key) {
        bucket = bucket->next;
    }
    return bucket;
}

corpus_index * create_index(void){
    int i;
    size_t bucket_size = INITIAL_INDEX_BUCKETS * sizeof(corpus_index_key *);

    corpus_index * index = (corpus_index *)malloc(sizeof(corpus_index));
    index->keys = (corpus_index_key **)malloc(bucket_size);
    for(i = 0; i < INITIAL_INDEX_BUCKETS; i++) {
        *(index->keys + i) = NULL;
    }
    index->mem_spaces = INITIAL_INDEX_BUCKETS;
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
