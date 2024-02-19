.PHONY: all clean rebuild my_server my_client unlink

BUILD_DIR := build
CLIENT_DIR := client
SERVER_DIR := server
UTILS_DIR := utils
CLIENT_BUILD_DIR := $(BUILD_DIR)/client
SERVER_BUILD_DIR := $(BUILD_DIR)/server
UTILS_BUILD_DIR := $(BUILD_DIR)/utils

DIR_CHECK = @mkdir -p $(@D)

CLIENT_OBJ := $(patsubst $(CLIENT_DIR)/%.c, $(CLIENT_BUILD_DIR)/%.o, $(wildcard $(CLIENT_DIR)/*.c))
SERVER_OBJ := $(patsubst $(SERVER_DIR)/%.c, $(SERVER_BUILD_DIR)/%.o, $(wildcard $(SERVER_DIR)/*.c))
UTILS_OBJ := $(patsubst $(UTILS_DIR)/%.c, $(UTILS_BUILD_DIR)/%.o, $(wildcard $(UTILS_DIR)/*.c))

all: my_server my_client

my_server: $(SERVER_OBJ) $(UTILS_OBJ)
	gcc $^ -o $@ -g -lrt -lncurses -pthread

my_client: $(CLIENT_OBJ) $(UTILS_OBJ)
	gcc $^ -o $@ -g -lrt -lncurses -pthread

$(SERVER_BUILD_DIR)/%.o: $(SERVER_DIR)/%.c
	$(DIR_CHECK)
	gcc -c $< -o $@ -g -lrt -lncurses -pthread

$(CLIENT_BUILD_DIR)/%.o: $(CLIENT_DIR)/%.c
	$(DIR_CHECK)
	gcc -c $< -o $@ -g -lrt -lncurses -pthread

$(UTILS_BUILD_DIR)/%.o: $(UTILS_DIR)/%.c
	$(DIR_CHECK)
	gcc -c $< -o $@ -g -lrt -lncurses -pthread

unlink:
	gcc unlink_after_errorExit.c -lrt -o errUnlink
	./errUnlink

clean: unlink
	rm -rf *.o *.out my_client my_server errUnlink build

rebuild: clean all