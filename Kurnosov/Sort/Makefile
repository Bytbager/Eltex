PROJECT:= sort_test

.PHONY: all clean rebuild $(PROJECT)

CFLAGS := -g -lm

all: $(PROJECT)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -o $@ $(CFLAGS)

%.o: %.c
	gcc -c $< $(CFLAGS)

clean:
	rm -rf *.o *.out *.txt $(PROJECT)

rebuild: clean $(PROJECT)