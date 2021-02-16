#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfs.h"
#include "map.h"

MAP map;
int** visitedMap;

void allocateVisitedMap(MAP* map) {
    visitedMap = malloc(map->height * sizeof(int*));
    for (int i = 0; i < map->height; i++) {
        visitedMap[i] = calloc(map->width, sizeof(int));
    }
}

void deallocateVisitedMap(MAP* map) {
    for (int i = 0; i < map->width; i++) {
        free(visitedMap[i]);
    }
    free(visitedMap);
}

void printQueuePath(MAP* map, QUEUE* queue) {
    char path[200];
    int index = 0;
    while(queue->front) {
        path[index++] = queue->front->x + '0';
        path[index++] = ',';
        path[index++] = queue->front->y + '0';
        path[index++] = '-';
        path[index++] = '>';
        //printf("%d,%d\n", queue->front->x, queue->front->y);
        if (queue_front(queue)->value == FLOOR) {
            map->matrix[queue->front->x][queue->front->y] = 'x';
        }
        queue_pop(queue);
    }
    path[index-2] = '\0';
    printf("path: %s\n", path);
}

void printPath(MAP* map, STACK* stack) {
    char path[200];
    int index = 0;
    while(stack->top) {
        path[index++] = stack->top->x + '0';
        path[index++] = ',';
        path[index++] = stack->top->y + '0';
        path[index++] = '<';
        path[index++] = '-';
        //printf("%d,%d\n", stack->top->x, stack->top->y);
        if (stack_top(stack) == FLOOR) {
            map->matrix[stack->top->x][stack->top->y] = 'x';
        }
        stack_pop(stack);
    }
    path[index-2] = '\0';
    printf("path: %s\n", path);
}

int dfs_queue(MAP* map, int** visitedMap, QUEUE* queue, int currX, int currY) {
    if (visitedMap[currX][currY]) {
        return 0;
    }

    char c = map->matrix[currX][currY]; 
    if (c != FLOOR && c != START && c != END) {
        return 0;
    }

    visitedMap[currX][currY] = 1;
    queue_push(queue, c);
    NODE* back = queue_back(queue);
    back->x = currX;
    back->y = currY;

    if (c == END) {
        printf("Found on: %d,%d\n", currX, currY);
        return 1;
    }

    int dirX1 = currX + 1; 
    int dirY1 = currY + 1; 
    int dirX2 = currX - 1;
    int dirY2 = currY - 1;

    int result = 0;
    if (dirX1 < map->height) {
        result = dfs_queue(map, visitedMap, queue, dirX1, currY);
    }
    if (!result && dirX2 >= 0) {
        result = dfs_queue(map, visitedMap, queue, dirX2, currY);
    }
    if (!result && dirY1 < map->width) {
        result = dfs_queue(map, visitedMap, queue, currX, dirY1);
    }
    if (!result && dirY2 >= 0) {
        result = dfs_queue(map, visitedMap, queue, currX, dirY2);
    }
    if (!result) queue_pop(queue);
    return result;
}

int dfs(MAP* map, int** visitedMap, STACK* stack, int currX, int currY) {
    if (visitedMap[currX][currY]) {
        return 0;
    }

    char c = map->matrix[currX][currY]; 
    if (c != FLOOR && c != START && c != END) {
        return 0;
    }

    visitedMap[currX][currY] = 1;
    stack_push(stack, c);
    stack->top->x = currX;
    stack->top->y = currY;

    if (c == END) {
        printf("Found on: %d,%d\n", currX, currY);
        return 1;
    }

    int dirX1 = currX + 1; 
    int dirY1 = currY + 1; 
    int dirX2 = currX - 1;
    int dirY2 = currY - 1;

    int result = 0;
    if (dirX1 < map->height) {
        result = dfs(map, visitedMap, stack, dirX1, currY);
    }
    if (!result && dirX2 >= 0) {
        result = dfs(map, visitedMap, stack, dirX2, currY);
    }
    if (!result && dirY1 < map->width) {
        result = dfs(map, visitedMap, stack, currX, dirY1);
    }
    if (!result && dirY2 >= 0) {
        result = dfs(map, visitedMap, stack, currX, dirY2);
    }
    if (!result) stack_pop(stack);
    return result;

}

void findPath(MAP* map) {
    allocateVisitedMap(map);
    int initX, initY;
    findStart(map, &initX, &initY);
    printf("initial: (%d,%d)\n", initX, initY);
    QUEUE queue = { NULL };
    int result = dfs_queue(map, visitedMap, &queue, initX, initY);
    if (result) {
        printQueuePath(map, &queue);
    } else {
        printf("Could not find a way queue\n");
    }

/*    STACK stack;
    int result = dfs(map, visitedMap, &stack, initX, initY);
    if (result) {
        printPath(map, &stack);
    } else {
        printf("Could not find a way stack\n");
    }
*/
    deallocateVisitedMap(map);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Please inform which path you want to execute bfs in\n");
    }

    char* filename = argv[1];
    printf("Will try to find a way out in %s\n", filename);

    FILE* file;
    file = fopen(filename, "r");
    if (file == 0) {
        printf("Could not read file: %s\n", filename);
        exit(1);
    }
    buildMapForFile(&map, file);
    fclose(file);
    printMap(&map);
    findPath(&map);
    deallocateMap(&map);
    return 0;
}
