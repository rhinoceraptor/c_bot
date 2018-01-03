
/**
 * Parses command line options for IRC bot options
 */

#include "bot.h"

static int help_flag;

static char *help =
  "c_bot - simple IRC bot written in C\n"
  "Options:\n"
  "  -h | --help\n"
  "    Prints this help message\n"
  "  -n | --nickname\n"
  "    Set the nickname for the bot\n"
  "    Default: c_bot\n"
  "  -r | --realname\n"
  "    Set the realname for the bot\n"
  "    Default: c_bot\n"
  "  -o | --hostname\n"
  "    Set the hostname for the bot\n"
  "    Default: localhost\n"
  "  -s | --server\n"
  "    Set the server to connect to\n"
  "    Default: localhost\n"
  "  -p | --port\n"
  "    Set the server port to connect to\n"
  "    Default: 6667\n"
  "  -c | --channel\n"
  "    Connect to the given channel\n"
  "  -q | --quitmessage\n"
  "    Set the quit message\n\n"
  "Example usage:\n"
  "$ ./bot -n bot -s irc.my-irc-server.com -c #my-favorite-channel\n";

bot_options_t *parse_options (int argc, char *argv[]) {
  bot_options_t *bot_opts = malloc(sizeof(struct bot_options));

  int opt;

  struct option long_options[] = {
    { "help",        no_argument,       &help_flag, 1   },
    { "nickname",    required_argument, 0,          'n' },
    { "realname",    required_argument, 0,          'r' },
    { "hostname",    required_argument, 0,          'o' },
    { "server",      required_argument, 0,          's' },
    { "port",        required_argument, 0,          'p' },
    { "channel",     required_argument, 0,          'c' },
    { "quitmessage", required_argument, 0,          'q' },
    { 0, 0, 0, 0 }
  };

  const char *optstring = ":n:r:o:s:p:c:q:";
  int option_index = 0;

  while ((opt = getopt_long(argc, argv, optstring, long_options, &option_index)) != -1) {
    printf("before\n");
    size_t optarg_len = strlen(optarg) + 1;

    printf("optarg: %s\n", optarg);
    switch (opt) {
      case 'h':
        printf("%s\n", help);
        // TODO: exit
        break;
      case 'n':
        bot_opts->nickname = calloc(1, optarg_len * sizeof(char));
        strlcpy(bot_opts->nickname, optarg, optarg_len);
        break;
      case 'r':
        bot_opts->realname = calloc(1, optarg_len * sizeof(char));
        strlcpy(bot_opts->realname, optarg, optarg_len);
        break;
      case 'o':
        printf("host\n");
        bot_opts->host = calloc(1, optarg_len * sizeof(char));
        strlcpy(bot_opts->host, optarg, optarg_len);
        printf("host\n");
        break;
      case 's':
        bot_opts->server = calloc(1, optarg_len * sizeof(char));
        strlcpy(bot_opts->server, optarg, optarg_len);
        break;
      case 'p':
        bot_opts->server_port = calloc(1, optarg_len * sizeof(char));
        strlcpy(bot_opts->server_port, optarg, optarg_len);
        break;
      case 'c':
        printf("channel: %s\n", optarg);
        break;
      case 'q':
        bot_opts->quit_message = calloc(1, optarg_len * sizeof(char));
        strlcpy(bot_opts->quit_message, optarg, optarg_len);
        break;
    }
  }
}

