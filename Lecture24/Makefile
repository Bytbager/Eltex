CC = gcc
CFLAGS = -Wall -Werror -Wextra

all:
	make task1
	make fork_tree

task1:
	$(CC) $(CFLAGS) -o task1 task1.c

fork_tree:
	$(CC) $(CFLAGS) -o fork_tree fork_tree.c

clean:
	rm -rf fork_tree task1 *.out *.o

rebuild:
	make clean
	make all
