
/*
 * IRC bot written in C
 */

#include "bot.h"

static int sock_fd;
static char **channels;

#define FREE(str) { \
  if (str != NULL) { \
    free(str); \
    str = NULL; \
  } \
} \

void write_irc(char *mesg) {
  dprintf(sock_fd, "%s\r\n", mesg);
}

void say_irc(char *channel, char *mesg) {
  dprintf(sock_fd, "PRIVMSG %s :%s\r\n", channel, mesg);
}

void wall(char *mesg) {
  int i = 0;
  while (channels[i] != NULL) {
    dprintf(sock_fd, "PRIVMSG %s :%s\r\n", channels[i], mesg);
    i++;
  }
}

// Set the bot's nick, realname, etc
void configure_bot(void) {
  dprintf(sock_fd, "NICK %s\r\n", NICK);
  dprintf(sock_fd, "USER %s %s %s : %s\r\n", NICK, HOST, SERVER, REALNAME);
}

// Handle SIGINT cleanly (Ctrl-C)
void sigint_handler(int signal) {
  if (signal == SIGINT) {
    quit_irc();
  }
}

// Cleanly quit IRC
void quit_irc(void) {
  dprintf(sock_fd, "QUIT :%s\r\n", QUITMESG);
  close(sock_fd);
  exit(EXIT_SUCCESS);
}

// Iterate through the channels string array, and join each channel
void join_channels(void) {
  int i = 0;
  while (channels[i] != NULL) {
    dprintf(sock_fd, "JOIN %s\r\n", channels[i]);
    i++;
  }
}

// Main bot loop
void loop(void) {
  long read_len;
  char irc_buffer[MAX_IRC_LEN];
  irc_message *message = NULL;
  char *line;

  // Loop for as long as we are able to read from the socket
  while ((read_len = read(sock_fd, irc_buffer, MAX_IRC_LEN - 1))) {
    printf(">>>%s<<<\n\n", irc_buffer);
    // Copy the buffer to a new string
    line = calloc(1, read_len);
    strncpy(line, irc_buffer, read_len);

    // Check for PING
    if (strncmp(line, "PING", strlen("PING")) == 0) {
      write_irc("PONG");
    }
    // Else, check for a command
    else {
      //parse_line(line, message);
    }
  }
}

int main(void) {
  // Set up SIGINT handler (Ctrl-C)
  if (signal(SIGINT, sigint_handler) == SIG_ERR) {
    quit_irc();
  }

  // Connect to the IRC server */
  sock_fd = open_irc_socket(SERVER, PORT);

  // Set the bot's nick and real name */
  configure_bot();

  // Join channels */
  channels = (char *[]) CHANNELS;
  join_channels();

  printf("Connected to %s:%d\n", SERVER, PORT);

  loop();
}

