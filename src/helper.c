/*
 * helper - various helper functions
 */

#include <errno.h>
#include "bot.h"

// Parse the user, irc command, channel, and message from the line
void parse_line(char *line, char **nick, char **irc_cmd, char **channel, char **mesg) {
  // :jack!jack@yakko.cs.wmich.edu PRIVMSG #asdf :hello world!

  // Remove leading colon
  line++;

  char *line_ptr, *nick_ptr, *temp_nick, *temp_cmd, *temp_chan, *temp_mesg;

  // Split the message by spaces, and check for errors
  if ((temp_nick = strtok_r(line,      " ",    &line_ptr)) == NULL ||
      (temp_nick = strtok_r(temp_nick, "!",    &nick_ptr)) == NULL ||
      (temp_cmd  = strtok_r(NULL,      " ",    &line_ptr)) == NULL ||
      (temp_chan = strtok_r(NULL,      " ",    &line_ptr)) == NULL ||
      (temp_mesg = strtok_r(NULL,      "\r\n", &line_ptr)) == NULL) {
    printf("strtok failed!\n");
    return;
  }
  // If all strings were collected successfully, allocate strings for each
  else {
    temp_mesg++;

    // Allocate each string, and check for failure
    if ((*nick    = calloc(1, strlen(temp_nick + 1))) == NULL ||
        (*irc_cmd = calloc(1, strlen(temp_cmd  + 1))) == NULL ||
        (*channel = calloc(1, strlen(temp_chan + 1))) == NULL ||
        (*mesg    = calloc(1, strlen(temp_mesg + 1))) == NULL) {
      quit_irc();
    }

    strncpy(*nick, temp_nick, strlen(temp_nick));
    strncpy(*irc_cmd, temp_cmd, strlen(temp_cmd));
    strncpy(*channel, temp_chan, strlen(temp_chan));
    strncpy(*mesg, temp_mesg, strlen(temp_mesg));
  }
}

// Open the IRC socket to SERVER, PORT as defined in config.h
int open_socket(const char *server_name, const int port) {
  int sock_fd;

  int domain = AF_INET6;
  int type = SOCK_STREAM;
  int protocol = 0;

  // Create the socket
  if ((sock_fd = socket(domain, type, protocol)) == -1) {
    perror("Unable to create socket");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr = {
    .sin_family = PF_INET6,
    .sin_port = htons((uint16_t) port),
  };

  // Convert the server_name address to binary form, into server_addr.sin_addr
  if (inet_pton(domain, server_name, &server_addr.sin_addr) == -1) {
    perror("Converting server name failed");
    exit(EXIT_FAILURE);
  }

  // Connect to the server
  if (connect(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
    perror("Connecting to irc server failed");
    exit(EXIT_FAILURE);
  }

  return sock_fd;
}
