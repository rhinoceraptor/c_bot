
#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

/* IRC lines are at most 512 bytes long, plus a null terminator makes 513 */
#define MAX_IRC_LEN 513

/* bot.c */
void write_irc(char *mesg);
void say_irc(char *channel, char *mesg);
void configure_bot(void);
void sigint_handler(int signal);
void quit_irc(void);
void join_channels(char **channels);
void loop(void);

/* helper.c */
int open_irc_socket(const char *server_ip, const int port);


