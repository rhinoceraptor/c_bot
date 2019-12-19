/*
 * helper - various helper functions
 */

#include "bot.h"

// Parse the user, irc command, channel, and message from the line
void parse_line(char *line, irc_message *message) {
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
    if ((message->nick    = calloc(1, strlen(temp_nick + 1))) == NULL ||
        (message->command = calloc(1, strlen(temp_cmd  + 1))) == NULL ||
        (message->channel = calloc(1, strlen(temp_chan + 1))) == NULL ||
        (message->message    = calloc(1, strlen(temp_mesg + 1))) == NULL) {
      quit_irc();
    }

    // Copy from the temp string pointers into the fields
    strncpy(message->nick, temp_nick, strlen(temp_nick));
    strncpy(message->command, temp_cmd, strlen(temp_cmd));
    strncpy(message->channel, temp_chan, strlen(temp_chan));
    strncpy(message->message, temp_mesg, strlen(temp_mesg));
  }
}

// Open the IRC socket to SERVER, PORT as defined in config.h
int open_irc_socket(const char *server_ip, const int port) {
  int sock_fd;

  // Open an IPv4, TCP socket
  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
       dprintf(STDERR_FILENO, "Unable to open TCP socket!\n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in irc_addr = {
    .sin_family = AF_INET,
    .sin_port = htons((uint16_t) port),
  };

  // Convert the server_ip address to binary form, into irc_addr.sin_addr
  if (inet_pton(AF_INET, server_ip, &irc_addr.sin_addr) == -1) {
    dprintf(STDERR_FILENO, "Conversion of server IP to binary form failed!\n");
    exit(EXIT_FAILURE);
  }

  // Connect to the server
  if (connect(sock_fd, (struct sockaddr_in *) &irc_addr, sizeof(irc_addr)) == -1) {
    dprintf(STDERR_FILENO, "Failed to connect to the IRC server!\n");
    exit(EXIT_FAILURE);
  }

  return sock_fd;
}
