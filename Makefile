export SHELL=/bin/sh

CC=clang
FLAGS=-Weverything -Wall -Wpedantic -std=c99 -D_GNU_SOURCE

make: clean bot

bot: src/bot.c
	$(CC) $(FLAGS) src/bot.c -o bot

clean:
	rm -f *.gch bot *.o

