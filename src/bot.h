
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>

/* bot.c */
void write_irc(char *mesg);
void say_irc(char *channel, char *mesg);
int open_irc_socket(const char *server, const int port);


