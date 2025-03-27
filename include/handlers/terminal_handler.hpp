#pragma once

#include <termios.h>

class TerminalHandler {
  private:
    static struct termios term;

  public:
    void enableRawMode();
    static void disableRawMode();
    static void signalHandler(int signal);
    static void registerSignalHandler();
};
