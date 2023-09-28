.PHONY: all clean rebuild shop

all: shop

shop: $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -o $@ -g

%.o: %.c
	gcc -c $< -g

clean:
	rm -rf *.o *.out shop

rebuild: clean shop