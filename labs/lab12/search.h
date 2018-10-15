#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

struct engine_data
{
    int priority;
    char search_feed[150];
};

typedef struct engine_data ED;
ED search_list[300];

int global_count = 0;

void welcome();
void load_from_file();

#endif // SEARCH_H_INCLUDED
