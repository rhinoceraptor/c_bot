
/*
 * IRC bot written in C
 */

#include "bot.h"

void write_irc(char *mesg)
{
}

void say_irc(char *channel, char *mesg)
{
}

/* Open the IRC socket to SERVER, PORT as defined in config.h */
int open_irc_socket(const char *server, const int port)
{
  int sock_fd;

  /* Open an IPv4, TCP socket */
  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    dprintf(STDERR_FILENO, "Unable to open TCP socket!\n");
    exit(EXIT_FAILURE);
  }


  return sock_fd;
}

int main(int argc, char *argv[])
{
  int sock_fd = open_irc_socket(SERVER, PORT);

}

