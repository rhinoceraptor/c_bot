
/*
 * IRC bot written in C
 */

#include "bot.h"

//static char **channels;
//
//#define FREE(str) { \
//  if (str != NULL) { \
//    free(str); \
//    str = NULL; \
//  } \
//} \
//
//void write_irc(int socket, char *mesg) {
//  dprintf(sock_fd, "%s\r\n", mesg);
//}
//
//void say_irc(char *channel, char *mesg) {
//  dprintf(sock_fd, "PRIVMSG %s :%s\r\n", channel, mesg);
//}
//
//void wall(char *mesg) {
//  int i = 0;
//  while (channels[i] != NULL) {
//    dprintf(sock_fd, "PRIVMSG %s :%s\r\n", channels[i], mesg);
//    i++;
//  }
//}
//
//// Set the bot's nick, realname, etc
//void configure_bot(void) {
//  dprintf(sock_fd, "NICK %s\r\n", NICK);
//  dprintf(sock_fd, "USER %s %s %s : %s\r\n", NICK, HOST, SERVER, REALNAME);
//}
//

// Handle SIGINT cleanly (Ctrl-C)
void sigint_handler (int signal, int *socket) {
  if (signal == SIGINT) {
    quit_irc(*socket);
  }
}

// Cleanly quit IRC
__attribute__ ((noreturn)) void quit_irc (int socket) {
  printf("socket: %d\n", socket);
  //dprintf(sock_fd, "QUIT :%s\r\n", QUITMESG);
  //close(socket);
  exit(EXIT_SUCCESS);
}

//// Iterate through the channels string array, and join each channel
//void join_channels(void) {
//  int i = 0;
//  while (channels[i] != NULL) {
//    dprintf(sock_fd, "JOIN %s\r\n", channels[i]);
//    i++;
//  }
//}
//
//// Main bot loop
//void loop(void) {
//  long read_len;
//  char irc_buffer[MAX_IRC_LEN];
//  char *line, *nick, *irc_cmd, *channel, *mesg;
//
//  // Loop for as long as we are able to read from the socket
//  while ((read_len = read(sock_fd, irc_buffer, MAX_IRC_LEN - 1))) {
//    // Copy the buffer to a new string
//    line = calloc(1, (unsigned long) read_len);
//    strncpy(line, irc_buffer, (unsigned long) read_len);
//
//    // Check for PING
//    if (strncmp(line, "PING", strlen("PING")) == 0) {
//      write_irc((char *) "PONG");
//    }
//    // Else, check for a command
//    else {
//      nick = irc_cmd = channel = mesg = NULL;
//      parse_line(line, &nick, &irc_cmd, &channel, &mesg);
//
//      // parse_line will allocate nick, irc_cmd, channel and mesg, if they
//      // remain NULL, then line did not contain all of the elements
//      if (nick != NULL && irc_cmd != NULL && channel != NULL && mesg != NULL) {
//        if (strncmp(irc_cmd, "PRIVMSG", strlen("PRIVMSG")) == 0)
//          printf("%s | %s\n", nick, mesg);
//
//        FREE(nick);
//        FREE(irc_cmd);
//        FREE(channel);
//        FREE(mesg);
//      }
//    }
//
//    // Free the allocated string
//    FREE(line);
//  }
//}

int main (int argc, char *argv[]) {
  int socket = 5;

  // Set up SIGINT handler (Ctrl-C)
  if (signal(SIGINT, (void (*)(int))sigint_handler) == SIG_ERR) {
    quit_irc(socket);
  }

  bot_options_t *opts = parse_options(argc, argv);

//
//
//  // Connect to the IRC server
//  sock_fd = open_socket(SERVER, PORT);
//
//  // Set the bot's nick and real name
//  configure_bot();
//
//  // Join channels
//  channels = (char *[]) CHANNELS;
//  join_channels();
//
//  printf("Connected to %s:%d\n", SERVER, PORT);
//
//  loop();
}

