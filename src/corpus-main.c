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
#include <stdio.h>
#include <unistd.h>

#include "corpus.h"

static chain_options * parse_ops(int argc, char ** argv) {
    int c;
    int i;
    unsigned int ignoreCount = 0;
    int * ignore = NULL;
    char * ignoreStr = NULL;
    chain_options * options = create_default_ops();
    while((c = getopt(argc, argv, "d:")) != -1) {
        switch(c) {
            case 'd' :
                ignoreStr = optarg;
                ignoreCount = strlen(ignoreStr);
                ignore = (int *)malloc(ignoreCount * sizeof(int));
                for(i = 0; i < ignoreCount; i++) {
                     ignore[i] = (int)ignoreStr[i];
                }
                break;
        }
    }
    options->ignore = ignore;
    options->ignoreCount = ignoreCount;
    return options;
}

static void output_chain(corpus_root * root) {
    unsigned long int corpus_length = root->amount;
    corpus_chain * full_chain = root->root;
    int i, j;
    for(i = 0; i < corpus_length; i++) {
        corpus_chain * chain = full_chain + i;
        unsigned long int total_seen = chain->seen_total;
        unsigned long int corpus_amount = chain->corpus_amount;
        int value = chain->value;
        for(j = 0; j < corpus_amount; j++) {
            corpus_node * node = chain->corpus + j;
            double probability = (double)node->seen / (double)total_seen;
            printf("%c:%c:%.15f\n",value, node->other, probability);
        }
    }
}

int main(int argc, char ** argv) {
    chain_options * ops = parse_ops(argc, argv);
    corpus_root * root = generate_chain(ops);
    output_chain(root);
    free_options(ops);
    free_chain(root);
    return EXIT_SUCCESS;
}
