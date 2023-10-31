PROJECT:= system_v_hello

.PHONY: all clean rebuild $(PROJECT)_server $(PROJECT)_client

all: $(PROJECT)_server $(PROJECT)_client

$(PROJECT)_server: $(patsubst %.c, %.o, $(PROJECT)_server.c) errExit.o
	gcc $^ -o $@ -g

$(PROJECT)_client: $(patsubst %.c, %.o, $(PROJECT)_client.c) errExit.o
	gcc $^ -o $@ -g

%.o: %.c
	gcc -c $< -g

clean:
	rm -rf *.o *.out $(PROJECT)_client $(PROJECT)_server

rebuild: clean $(PROJECT)