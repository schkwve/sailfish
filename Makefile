CC := gcc
LD := ld

CFLAGS ?= -c -Wall -O3
LDFLAGS ?= -lm

NAME=tummy

SRC=$(shell find src -name "*.c" -type f)
OBJ=$(SRC:.c=.o)

.PHONY: all
all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean:
	@rm -r $(OBJ) $(NAME)