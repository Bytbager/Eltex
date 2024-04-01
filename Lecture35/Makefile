PROJECT:= sig_prog

.PHONY: all clean rebuild $(PROJECT)

CFLAGS := -g

all: $(PROJECT)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -o $@ $(CFLAGS)

%.o: %.c
	gcc -c $< $(CFLAGS)

clean:
	rm -rf *.o *.out *.txt $(PROJECT)

rebuild: clean $(PROJECT)