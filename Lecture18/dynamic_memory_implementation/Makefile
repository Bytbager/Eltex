.PHONY: all clean rebuild subscriber_list

all: subscriber_list

subscriber_list: $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -o $@ -g

%.o: %.c
	gcc -c $< -g

clean:
	rm -rf *.o *.out subscriber_list

rebuild: clean subscriber_list