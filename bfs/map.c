#include <stdlib.h>
#include "map.h"

void allocateMap(MAP* map) {
    map->matrix = malloc(sizeof(char*) * map->height);
    for (int i = 0; i < map->height; i++) {
        map->matrix[i] = malloc(sizeof(char) * (map->width+1));
    }
}

void deallocateMap(MAP* map) {
    for (int i = 0; i < map->height; i++) {
        free(map->matrix[i]);
    }
    free(map->matrix);
}

void fillMapFromFile(MAP* map, FILE* file) {
    for (int i = 0; i < map->height; i++) {
        fscanf(file, "%s", map->matrix[i]);
    }
}

void printMap(MAP* map) {
    for (int i = 0; i < map->height; i++) {
        printf("%s\n", map->matrix[i]);
    }
}

void buildMapForFile(MAP* map, FILE* file) {
    int height, width;
    fscanf(file, "%d %d", &height, &width);
    printf("Map with height: %d, width:%d\n", height, width);
    map->height = height;
    map->width = width;
    allocateMap(map);
    fillMapFromFile(map, file);
}

void findStart(MAP* map, int* x, int* y) {
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++) {
            if (map->matrix[i][j] == START) {
                (*x) = i;
                (*y) = j;
                return;
            }
        }
    }
}
