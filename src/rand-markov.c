#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct markov_state;

typedef struct
{
    float range;
    struct markov_state * transition;

} markov_path; 

typedef struct markov_state {

    int value;
    int path_count;
    markov_path * paths;
} markov_state;

markov_state * find_state(markov_state * root, int count) {
    return NULL;
}

int path_sort(const void * left, const void * right) {
    markov_path * leftPath = (markov_path *)left;
    markov_path * rightPath = (markov_path *)right;
    if(leftPath->range < rightPath->range) {
       return -1;
    }
    else if(leftPath->range > rightPath->range) {
       return 1;
    }
    else {
       return 0;
    }
}

int main(void) {
    int i;
    int total = 0;
    markov_state * root = NULL;
    char buffer[1024]; 
    srand(time(NULL));
    while(fgets(buffer, 1024, stdin) != NULL) {
        char state;
        char next;
        float transition;
        sscanf(buffer, "%c:%c:%f", &state, &next, &transition);
        markov_state * mstate = find_state(root, total);
        if(mstate == NULL) {
           ++total;
           root = (markov_state *)realloc(root, total * sizeof(markov_state));
           mstate = root + (total - 1);
           mstate->value = state;
           mstate->paths = NULL;
           mstate->path_count = 0;
        }
        markov_state * mnext = find_state(root, total);
        if(mnext == NULL) {
           ++total;
           root = (markov_state *)realloc(root, total * sizeof(markov_state));
           mnext = root + (total - 1);
           mnext->value = next;
           mnext->paths = NULL;
           mnext->path_count = 0;
        }
        mstate->path_count++;
        mstate->paths = (markov_path *)realloc(mstate->paths, mstate->path_count * sizeof(markov_path));
        markov_path * new_path = mstate->paths + (mstate->path_count - 1);
        new_path->range = transition;
        new_path->transition = mnext;
    }
    for(i = 0; i < total; i++) {
        markov_state * sort_state = root + i;
        qsort(sort_state->paths,
              sort_state->path_count,
              sizeof(markov_path),
              &path_sort);
              
    }
    
    return 0;
}
