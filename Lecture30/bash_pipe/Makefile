PROJECT:= bash_pipe

.PHONY: all clean rebuild $(PROJECT)

all: $(PROJECT)

$(PROJECT): $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -o $@ -g

%.o: %.c
	gcc -c $< -g

clean:
	rm -rf *.o *.out $(PROJECT)

rebuild: clean $(PROJECT)