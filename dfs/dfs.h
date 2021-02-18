#ifndef DFS_H
#define DFS_H

#include "map.h"
#include "../data-structures/stack/stack.h"
#include "../data-structures/queue/queue.h"

int** allocateVisitedMap(MAP* map);
void deallocateVisitedMap(MAP* map, int** visitedMap);
void findPath(MAP* map);
int dfs(MAP* map, int** visitedMap, STACK* stack, int currentX, int currentY);
int dfs_queue(MAP* map, int** visitedMap, QUEUE* stack, int currentX, int currentY);
#endif
