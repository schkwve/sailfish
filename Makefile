CC := gcc
LD := ld

CFLAGS ?= -c -std=c99 -Wall -O3
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -g4
endif
LDFLAGS ?= -lm

NAME=tummy

SRC=$(shell find src -name "*.c" -type f)
OBJ=$(SRC:.c=.o)

.PHONY: all
all: clean $(NAME) # Build everything

.PHONY: help
help: # Print help
	@grep '^[^.#]\+:\s\+.*#' Makefile | \
	gsed "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "\033[93m"`\1`printf "\033[0m"`	\3 [\2]/" | \
	expand -t20

%.o: %.c
	@printf " CC  $^\n"
	@$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@printf " CC  $^\n"
	@$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean: # Clean generated files
	@rm -rf $(OBJ) $(NAME)