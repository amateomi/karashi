CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -D_DEFAULT_SOURCE
CFLAGS += -O2 -s -DNDEBUG # Optimizations

# GNU readline library
CFLAGS += -I/usr/include/readline
LIBS = -lreadline

_SRC = built-in.c child.c executor.c init.c main.c parser.c prompt.c scanner.c utility.c
SRC = $(patsubst %,src/%,$(_SRC))

all: $(SRC)
	$(CC) $(CFLAGS) -o kara $^ $(LIBS)

.PHONY: install
install:
	cp kara /usr/bin/

.PHONY: uninstall
uninstall:
	rm /usr/bin/kara

.PHONY: test
.ONESHELL:
test:
	cat test/cases.sh | kara
