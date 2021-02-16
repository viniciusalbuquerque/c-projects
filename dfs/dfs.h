#ifndef BFS_H
#define BFS_H

#include "map.h"
#include "../data-structures/stack/stack.h"
#include "../data-structures/queue/queue.h"

void allocateVisitedMap(MAP* map);
void deallocateVisitedMap(MAP* map);
void findPath(MAP* map);
int dfs(MAP* map, int** visitedMap, STACK* stack, int currentX, int currentY);
int dfs_queue(MAP* map, int** visitedMap, QUEUE* stack, int currentX, int currentY);
#endif
