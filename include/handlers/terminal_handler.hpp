#ifndef TERMINAL_HANDLER_HPP
#define TERMINAL_HANDLER_HPP

#include <termios.h>

class TerminalHandler {
private:
  static struct termios term;

public:
  void enableRawMode();
  static void disableRawMode();
  static void signalHandler(int signal);
};

#endif // !TERMINAL_HANDLER_HPP
