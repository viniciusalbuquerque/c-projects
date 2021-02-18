#ifndef BFS_H
#define BFS_H
#include "map.h"

int** allocateVisitedMap(int height, int width);
void deallocateVisitedMap(int** visitedMap, int height);
void findPath(MAP* map);
#endif
