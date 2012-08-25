#include <stdio.h>

#include "corpus.h"

int main(void) {
    corpus_root * root = generate_chain(stdin);
    int i, j;
    for(i = 0; i < root->amount; i++) {
        corpus_chain * chain = root->root + i;
        float total_seen = chain->seen_total;
        int value = chain->value;
        for(j = 0; j < chain->corpus_amount; j++) {
            corpus_node * node = chain->corpus + j;
            float probability = (float)node->seen / total_seen;
            printf("%c:%c:%f\n",value, node->other, probability);
        }
    }
    return 0;
}
