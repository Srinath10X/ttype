#include "../include/terminal_handler.hpp"
#include "../include/constants.hpp"
#include <iostream>
#include <unistd.h>

struct termios TerminalHandler::term;

void TerminalHandler::enableRawMode() {
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);

  std::cout << WIPE_SCREEN << HIDE_CURSOR;
}

void TerminalHandler::disableRawMode() {
  term.c_lflag |= (ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &term);

  std::cout << WIPE_SCREEN << SHOW_CURSOR;
  exit(0);
}

void TerminalHandler::signalHandler(int signal) {
  TerminalHandler::disableRawMode();
}
