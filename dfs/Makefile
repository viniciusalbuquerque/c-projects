CC = $(CROSS_TOOL) gcc 
CFLAGS = -Wall -g -Werror

APP_NAME = dfs

all: $(APP_NAME)

dfs: stack.o map.o dfs.o queue.o
	$(CC) map.o dfs.o stack.o queue.o -o dfs

map.o:
	$(CC) -c $(CFLAGS) map.c

dfs.o:
	$(CC) -c $(CFLAGS) dfs.c

stack.o:
	$(CC) -c $(CFLAGS) ../data-structures/stack/stack.c

queue.o:
	$(CC) -c $(CFLAGS) ../data-structures/queue/queue.c

clear:
	rm -rf *.o
