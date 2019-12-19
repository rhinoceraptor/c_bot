export SHELL=/bin/bash

CC=clang
FLAGS=-Wall -Wpedantic -std=c99 -D_GNU_SOURCE
SO_FLAGS=-shared -undefined dynamic_lookup
CMD_FILES := $(wildcard cmds/*.c)

make: clean bot

bot: src/bot.c
	$(CC) $(FLAGS) src/bot.c src/helper.c -o bot

commands: $(CMD_FILES)
	$(CC) $(SO_FLAGS) src/bot.c src/helper.c -o bot

clean:
	rm -f *.gch bot *.o

