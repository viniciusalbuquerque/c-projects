#ifndef CUSTOM_MAP_H
#define CUSTOM_MAP_H
#include <stdio.h>

#define START 'A'
#define END 'B'
#define FLOOR '.'

typedef struct map {
    char** matrix;
    int height;
    int width;
} MAP;

void allocateMap(MAP* map);
void deallocateMap(MAP* map);
void fillMapFromFile(MAP* map, FILE* file);
void buildMapForFile(MAP* map, FILE* file);
void printMap(MAP* map);
void findStart(MAP* map, int* x, int* y);

#endif
