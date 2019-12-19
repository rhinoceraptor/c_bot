#include "../src/interface.h"

irc_response echo (irc_message *message);

irc_command_info get_info () {
  irc_command_info info = {
    .name = "echo",
    .command = echo
  };
  return info;
}

irc_response echo (irc_message *message) {
  irc_response response = {
    .message = message->message,
    .channel = message->channel
  };
  return response;
}

