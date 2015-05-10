export SHELL=/bin/bash

CC=clang
FLAGS=-Weverything -Wall -Wpedantic -std=c99 -D_GNU_SOURCE

make: clean bot

bot: src/bot.c
	$(CC) $(FLAGS) src/bot.c src/helper.c -o bot

clean:
	rm -f *.gch bot *.o

