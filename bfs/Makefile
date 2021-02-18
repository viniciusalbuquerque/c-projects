CC = $(CROSS_TOOL) gcc 
CFLAGS = -Wall -g -Werror

APP_NAME = bfs

all: $(APP_NAME)

bfs: map.o bfs.o queue.o
	$(CC) map.o bfs.o queue.o -o bfs

map.o:
	$(CC) -c $(CFLAGS) map.c

bfs.o:
	$(CC) -c $(CFLAGS) bfs.c

queue.o:
	$(CC) -c $(CFLAGS) ../data-structures/queue/queue.c

clear:
	rm -rf *.o bfs
