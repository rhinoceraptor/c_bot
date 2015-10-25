
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

// IRC lines are at most 512 bytes long, plus a null terminator makes 513
#define MAX_IRC_LEN 513

// bot.c
void write_irc(char *mesg);
void say_irc(char *channel, char *mesg);
void wall(char *mesg);
void configure_bot(void);
void sigint_handler(int signal);
__attribute__ ((noreturn)) void quit_irc(void);
void join_channels(void);
void loop(void);

// helper.c
void parse_line(char *line, char **nick, char **irc_cmd, char **channel, char **mesg);
char *parse_nick(char *line);
char *parse_irc_command(char *line);
char *parse_channel(char *line);
int open_irc_socket(const char *server_ip, const int port);


