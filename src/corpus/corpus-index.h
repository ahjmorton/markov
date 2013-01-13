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

#ifndef CORPUS_INDEX_HEADER
#define CORPUS_INDEX_HEADER


/**
 * These structures are not designed to be read 
 * directly so don't refer to any of their elements.
 * Use the methods provided!
 */
struct __corpus_index_value {
    int value;
    unsigned long int node_index;
    struct __corpus_index_value * next;
};

#define corpus_index_value struct __corpus_index_value

struct __corpus_index_key {
    int key;
    unsigned long int chain_index;
    struct __corpus_index_key * next;

    unsigned int value_count;
    unsigned int mem_spaces;
    corpus_index_value ** values;

};

#define corpus_index_key struct __corpus_index_key

struct __corpus_index{
    unsigned int key_count;
    unsigned int mem_spaces;
    corpus_index_key ** keys;   
};

#define corpus_index struct __corpus_index

corpus_index_value * add_index_value(corpus_index_key * key, unsigned long int node_index, int value);

corpus_index_value * find_index_value(corpus_index_key * key, int value);

corpus_index_key * add_index_key(corpus_index * index, unsigned long int chain_index, int key);

corpus_index_key * find_index_key(corpus_index * index, int key);

corpus_index * create_index(void);

void free_index(corpus_index * index);

#endif
