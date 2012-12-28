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
    int i, j;
    for(i = 0; i < root->amount; i++) {
        corpus_chain * chain = root->root + i;
        unsigned long int total_seen = chain->seen_total;
        int value = chain->value;
        for(j = 0; j < chain->corpus_amount; j++) {
            corpus_node * node = chain->corpus + j;
            double probability = (double)node->seen / (double)total_seen;
            printf("%c:%c:%.15f\n",value, node->other, probability);
        }
    }
    free_chain(root);
    return 0;
}
