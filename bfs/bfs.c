#include <stdio.h>
#include <stdlib.h>
#include "bfs.h"
#include "map.h"
#include "../data-structures/queue/queue.h"

int** allocateVisitedMap(int height, int width) {
    int** visitedMap = malloc(sizeof(int*) * height);
    for (int i = 0; i < height; i++) {
        visitedMap[i] = calloc(width, sizeof(int));
    }
    return visitedMap;
}

void deallocateVisitedMap(int** visitedMap, int height) {
    for (int i = 0; i < height; i++) {
        free(visitedMap[i]);
    }
    free(visitedMap);
}

int validMove(MAP* map, int x, int y) {
    if ((x < 0 || x >= map->height) || (y < 0 || y >= map-> width)) {
        return 0;
    }
    char move = map->matrix[x][y];
    return (move == FLOOR || move == START || move == END);
}

NODE* createNode(int x, int y, char value, NODE* next) {
    NODE* node = malloc(sizeof(NODE));
    node->value = value;
    node->x = x;
    node->y = y;
    node->next = next;
    return node;
}

void printPath(QUEUE* queue) {    
    char path[200];    
    int index = 0;    
    while(queue->front) {    
        path[index++] = queue->front->x + '0';    
        path[index++] = ',';    
        path[index++] = queue->front->y + '0';    
        path[index++] = '-';    
        path[index++] = '>';    
        queue_pop(queue);    
    }    
    path[index-2] = '\0';    
    printf("path: %s\n", path);    
}

void deallocateQueue(QUEUE* queue) {
    while(queue_front(queue)) {
        queue_pop(queue);
    }
}

void bfs(MAP* map, int initialX, int initialY) {
    int** visitedMap = allocateVisitedMap(map->height, map->width);
    char currentFloor = map->matrix[initialX][initialY];
    NODE* node = createNode(initialX, initialY, currentFloor, NULL);
    QUEUE queue = { node };
    int currX = initialX;
    int currY = initialY;
    int found = 0;
    NODE* front = queue_front(&queue);
    QUEUE visitedQueue = { NULL };
    while (front) {
        currX = front->x;
        currY = front->y;
        //printf("current: %d,%d\n", currX, currY);
        visitedMap[currX][currY] = 1;
        char current = map->matrix[currX][currY];
        queue_push_node(&visitedQueue, createNode(currX, currY, current, NULL));
        if (current == END) {
            found = 1;
            break;
        }

        int down = currX + 1;
        int up = currX - 1;
        int right = currY + 1;
        int left = currY - 1;

        if (validMove(map, down, currY) && !visitedMap[down][currY]) {
            visitedMap[down][currY] = 1;
            queue_push_node(&queue, createNode(down, currY, map->matrix[down][currY], NULL));
        }
        if (validMove(map, up, currY) && !visitedMap[up][currY]) {
            visitedMap[up][currY] = 1;
            queue_push_node(&queue, createNode(up, currY, map->matrix[up][currY], NULL));
        }
        if (validMove(map, currX, right) && !visitedMap[currX][right]) {
            visitedMap[currX][right] = 1;
            queue_push_node(&queue, createNode(currX, right, map->matrix[currX][right], NULL));
        }
        if (validMove(map, currX, left) && !visitedMap[currX][left]) {
            visitedMap[currX][left] = 1;
            queue_push_node(&queue, createNode(currX, left, map->matrix[currX][left], NULL));
        }
        queue_pop(&queue);
        front = queue_front(&queue);
    }

    printf("From: %d,%d\n", initialX, initialY);
    printPath(&visitedQueue);
    if (found) {
        printf("Found on: %d,%d\n", front->x, front->y);
    } else {
        printf("Could not find exit\n");
    }

    deallocateQueue(&queue);
    deallocateVisitedMap(visitedMap, map->height);
}

void findPath(MAP* map) {
    int x,y;
    findStart(map, &x, &y);
    bfs(map, x, y);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Pass filename\n");
        return 1;
    }

    char* filename = argv[1];
    printf("filename: %s\n", filename);

    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Could not open file: %s\n", filename);
        return 1;
    }

    MAP map;
    buildMapForFile(&map, file);
    fclose(file);
    printMap(&map);
    findPath(&map);
    deallocateMap(&map);

    return 0;
}
