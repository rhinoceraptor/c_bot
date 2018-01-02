
/*
 * IRC bot written in C
 */

#include "bot.h"

//static int sock_fd;
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
//// Handle SIGINT cleanly (Ctrl-C)
//void sigint_handler(int signal) {
//  if (signal == SIGINT) {
//    quit_irc();
//  }
//}
//
//// Cleanly quit IRC
//__attribute__ ((noreturn)) void quit_irc(void) {
//  dprintf(sock_fd, "QUIT :%s\r\n", QUITMESG);
//  close(sock_fd);
//  exit(EXIT_SUCCESS);
//}
//
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

bot_options *parse_options (int argc, char *argv[]) {
  char *help =
    "c_bot - simple IRC bot written in C\n"
    "options:\n"
    "  -n | --nickname\n"
    "    Set the nickname for the bot\n"
    "  -r | --realname\n"
    "    Set the realname for the both\n"
    "  -h | --hostname\n"
    "    Set the hostname for the bot\n"
    "  -s | --server\n"
    "    Set the server to connect to\n"
    "  -p | --port\n"
    "    Set the server port to connect to\n"
    "  -c | --channel\n"
    "    Connect to the given channel\n"
    "  -q | --quitmessage\n"
    "    Set the quit message\n";

  int opt;

  static struct option long_options[] = {
    { "nickname", required_argument, 0, 'n' },
    { "realname", required_argument, 0, 'r' },
    { "hostname", required_argument, 0, 'h' },
    { "server", required_argument, 0, 's' },
    { "port", required_argument, 0, 'p' },
    { "channel", required_argument, 0, 'c' },
    { "quitmessage", required_argument, 0, 'q' },
    { 0, 0, 0, 0}
  };

  const char *optstring = ":n:r:h:s:p:c:q:";
  int option_index = 0;

  while ((opt = getopt_long(argc, argv, optstring, long_options, option_index)) != -1) {
    switch (opt) {
      case 'n':
        printf("nickname: %s\n", optarg);
        break;
      case 'r':
        printf("realname: %s\n", optarg);
        break;
      case 'h':
        printf("hostname: %s\n", optarg);
        break;
      case 's':
        printf("server: %s\n", optarg);
        break;
      case 'p':
        printf("port: %s\n", optarg);
        break;
      case 'c':
        printf("channel: %s\n", optarg);
        break;
      case 'q':
        printf("quitmessage: %s\n", optarg);
        break;
    }
  }
}

int main(int argc, char *argv[]) {
  // Set up SIGINT handler (Ctrl-C)
  //if (signal(SIGINT, sigint_handler) == SIG_ERR) {
  //  exit(0);
  //  //quit_irc();
  //}

  bot_options *opts = parse_options(argc, argv);

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

