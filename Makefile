.POSIX:
.SUFFIXES:

CFLAGS := -O3 -Wall -Wextra -pedantic

PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

all: wordle-solver

wordle-solver: main.c guesses.h answers.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@

clean:
	rm -f wordle-solver

install: wordle-solver
	install -Dm755 wordle-solver $(BINDIR)/wordle-solver

uninstall:
	rm -f $(BINDIR)/wordle-solver

.PHONY: all clean install uninstall
