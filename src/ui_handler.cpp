#include "../include/ui_handler.hpp"
#include "../include/constants.hpp"
#include <iostream>
#include <unistd.h>

void UiHandler::wipeAndResetScreen() { std::cout << WIPE_SCREEN RESET; }

void UiHandler::getContext() { ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); }

void UiHandler::paddingTop(unsigned offset) {
  std::cout << std::string(window.ws_row - offset, '\n');
}

void UiHandler::paddingLeft(unsigned offset) {
  std::cout << std::string(window.ws_col - offset, ' ');
}

void UiHandler::alignContentWithOffset(unsigned offsetX, unsigned offsetY) {
  std::cout << std::string((window.ws_row - offsetY) / 2, '\n')
            << std::string((window.ws_col - offsetX) / 2, ' ');
}
