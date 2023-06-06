CC := gcc
LD := ld

CFLAGS += -c -std=c99 -Wall -O3
DEBUG ?= 1
ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG -g3
endif
LDFLAGS += -lm -lssl -lcrypto

NAME=sailfish

SRC=$(shell find src -name "*.c" -type f)
OBJ=$(SRC:.c=.o)

.PHONY: all
all: clean $(NAME) # Build everything

.PHONY: format
format: # Format the code as described in .clang-format
	find src -type f -name "*.c" -o -name "*.h" | xargs clang-format -i

.PHONY: help
help: # Print help
	@grep '^[^.#]\+:\s\+.*#' Makefile | \
	gsed "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "\033[93m"`\1`printf "\033[0m"`	\3 [\2]/" | \
	expand -t20

%.o: %.c
	@printf " CC  $^\n"
	@$(CC) $(CFLAGS) $< -o $@

$(NAME): $(OBJ)
	@printf " LD  $@\n"
	@$(CC) $^ $(LDFLAGS) -o $@

.PHONY: clean
clean: # Clean generated files
	@rm -rf $(OBJ) $(NAME)