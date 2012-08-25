#include <stdio.h>

#include "corpus.h"

int main(void) {
    corpus_root * root = generate_chain(stdin);
    int i, j;
    for(i = 0; i < root->amount; i++) {
        corpus_chain * chain = root->root + i;
        printf("%i)K:%c S:%i :\n", i, chain->value, chain->seen_total);
        for(j = 0; j < chain->corpus_amount; j++) {
            corpus_node * node = chain->corpus + j;
            printf("\t%c:%i\n", node->other, node->seen);
        }
    }
    return 0;
}
