PROJECT:= my_mc

.PHONY: all clean rebuild $(PROJECT)

all: $(PROJECT)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -o $@ -g -lncurses

%.o: %.c
	gcc -c $< -g -lncurses

clean:
	rm -rf *.o *.out *.txt $(PROJECT)

rebuild: clean $(PROJECT)