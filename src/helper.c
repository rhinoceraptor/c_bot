/*
 * helper - contains low level network logic
 */

#include "bot.h"

/* Open the IRC socket to SERVER, PORT as defined in config.h */
int open_irc_socket(const char *server_ip, const int port)
{
  int sock_fd;

  /* Open an IPv4, TCP socket */
  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    dprintf(STDERR_FILENO, "Unable to open TCP socket!\n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in irc_addr = {
    .sin_family = AF_INET,
    .sin_port = htons((uint16_t) port),
  };

  /* Convert the server_ip address to binary form, into irc_addr.sin_addr */
  if (inet_pton(AF_INET, server_ip, &irc_addr.sin_addr) == -1)
  {
    dprintf(STDERR_FILENO, "Conversion of server IP to binary form failed!\n");
    exit(EXIT_FAILURE);
  }

  /* Connect to the server */
  if (connect(sock_fd, (struct sockaddr_in *) &irc_addr, sizeof(irc_addr)) == -1)
  {
    dprintf(STDERR_FILENO, "Failed to connect to the IRC server!\n");
    exit(EXIT_FAILURE);
  }

  return sock_fd;
}
