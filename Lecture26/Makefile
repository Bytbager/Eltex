.PHONY: all clean rebuild pthread_increment

override CFLAGS := -pthread -g

all: pthread_increment

pthread_increment: $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $(CFLAGS) $^ -o $@

%.o: %.c
	gcc $(CFLAGS) -c $^

clean:
	rm -rf pthread_increment *.o *.out

rebuild: clean pthread_increment