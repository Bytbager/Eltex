.PHONY: all clean rebuild binary_operations byte_shift

override CFLAGS := -Wall -Werror -Wextra
BINARY_OPERATIONS_DIR := binary_operations
BYTE_SHIFT_DIR := byte_shift
HEXADECIMAL_NUMBER_DIR := hexadecimal_number

all: binary_operations byte_shift

binary_operations: $(patsubst $(BINARY_OPERATIONS_DIR)/%.c, %.o, $(wildcard $(BINARY_OPERATIONS_DIR)/*.c))
		gcc $(CFLAGS) $^ -o $@.out

byte_shift: $(patsubst $(BYTE_SHIFT_DIR)/%.c, %.o, $(wildcard $(BYTE_SHIFT_DIR)/*.c))
		gcc $(CFLAGS) $^ -o $@.out

hexadecimal_number: $(patsubst $(HEXADECIMAL_NUMBER_DIR)/%.c, %.o, $(wildcard $(HEXADECIMAL_NUMBER_DIR)/*.c))
		gcc $(CFLAGS) $^ -o $@.out

%.o: $(BINARY_OPERATIONS_DIR)/%.c
		gcc $(CFLAGS) -c $<

%.o: $(BYTE_SHIFT_DIR)/%.c
		gcc $(CFLAGS) -c $<

%.o: $(HEXADECIMAL_NUMBER_DIR)/%.c
		gcc $(CFLAGS) -c $<

clean:
		rm -rf *.o build *.out

rebuild:
		make clean
		make all