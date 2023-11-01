PROJECT:= posix_hello

.PHONY: all clean rebuild $(PROJECT)_server $(PROJECT)_client unlink

all: $(PROJECT)_server $(PROJECT)_client

$(PROJECT)_server: $(patsubst %.c, %.o, $(PROJECT)_server.c) errExit.o
	gcc $^ -o $@ -g -lrt

$(PROJECT)_client: $(patsubst %.c, %.o, $(PROJECT)_client.c) errExit.o
	gcc $^ -o $@ -g -lrt

%.o: %.c
	gcc -c $< -g -lrt

unlink:
	gcc unlink_after_errorExit.c -lrt -o errUnlink
	./errUnlink

clean: unlink
	rm -rf *.o *.out $(PROJECT)_client $(PROJECT)_server errUnlink

rebuild: clean $(PROJECT)