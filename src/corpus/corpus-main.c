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

#include "corpus.h"

int main(void) {
    corpus_root * root = generate_chain(stdin);
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
    free_chain(root);
    return 0;
}
