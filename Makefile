.POSIX:
.SUFFIXES:

all: wordle-solver

wordle-solver: main.c guesses.h answers.h
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
