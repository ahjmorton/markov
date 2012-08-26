#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct markov_path
{
    float range;
    int transition;

}; 

struct markov_state {

    int value;
    int path_count;
    struct markov_path * paths;
};

typedef struct markov_state markov_state;
typedef struct markov_path markov_path;

static markov_state * find_state(markov_state * root, int count, int value) {
    int i;
    for(i = 0; i < count; i++) {
        markov_state * current = root + i;
        if(current->value == value) {
            return current;
        }
    }
    return NULL;
}

static int path_sort(const void * left, const void * right) {
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

static markov_path * find_path(markov_path * paths, int count, float range) {
    int i;
    for(i = 0; i < count; i++) {
        markov_path * path = paths + i;
        if(path->range > range) {
            return path;
        }
    }
    // Take the last one, presumbly
    return paths + (count - 1);
    
}

int main(void) {
    srand(time(NULL));
    int i;
    int total = 0;
    markov_state * root = NULL;
    char buffer[1024]; 
    while(fgets(buffer, 1024, stdin) != NULL) {
        int state;
        char c_state;
        int next;
        char c_next;
        float transition;
        sscanf(buffer, "%c:%c:%f", &c_state, &c_next, &transition);
        state = (int)c_state;
        next = (int)c_next;
        markov_state * mstate = find_state(root, total, state);
        if(mstate == NULL) {
           ++total;
           root = (markov_state *)realloc(root, total * sizeof(markov_state));
           mstate = root + (total - 1);
           mstate->value = state;
           mstate->paths = NULL;
           mstate->path_count = 0;
        }
        markov_state * mnext = find_state(root, total, next);
        if(mnext == NULL) {
           ++total;
           printf("%i * %i = %i\n", total, sizeof(markov_state), total * sizeof(markov_state));
           root = (markov_state *)realloc(root, total * sizeof(markov_state));
           mnext = root + (total - 1);
           mnext->value = next;
           mnext->paths = NULL;
           mnext->path_count = 0;
        }
        (mstate->path_count)++;
        mstate->paths = (markov_path *)realloc(mstate->paths, (mstate->path_count) * sizeof(markov_path));
        markov_path * new_path = (mstate->paths) + ((mstate->path_count) - 1);
        new_path->range = transition;
        new_path->transition = mnext->value;
    }
    for(i = 0; i < total; i++) {
        markov_state * sort_state = root + i;
        qsort(sort_state->paths,
              sort_state->path_count,
              sizeof(markov_path),
              &path_sort);
              
    }
    int start = rand() % total;
    printf("start is %i \n", start);
    markov_state * current = root + start;
    printf("current is %c \n", current->value);
    for(i = 0; i < total; i++) {
        markov_state * fuckingCheck = current + i;
        printf("Fucking check at %p : %c %p %i\n", fuckingCheck, fuckingCheck->value, fuckingCheck->paths, fuckingCheck->path_count);
    }
    for(i = 0; i < 100; i++) {
        fputc(current->value, stdout);
        float next_range = (float)(rand() % 101) / 100;
        printf(" next range is %f\n", next_range);
        printf("paths here is %p and count is %i\n", current->paths, current->path_count);
        markov_path * path_to_follow = find_path(current->paths, current->path_count, next_range);
        
        current = find_state(root, total, path_to_follow->transition);
            
    }
    return 0;
}
