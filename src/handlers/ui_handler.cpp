#include <constants.hpp>
#include <handlers/ui_handler.hpp>
#include <iostream>
#include <unistd.h>

void UiHandler::wipeAndResetScreen() { std::cout << WIPE_SCREEN RESET; }

void UiHandler::getContext() { ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); }

void UiHandler::paddingLeft(unsigned left_padding) { std::cout << std::string(left_padding, ' '); }

void UiHandler::paddingTop(unsigned top_padding) { std::cout << std::string(top_padding, '\n'); }

void UiHandler::paddingTopWithOffset(unsigned offset) { std::cout << std::string((window.ws_row - offset) / 2, '\n'); }

void UiHandler::paddingLeftWithOffset(unsigned offset) { std::cout << std::string((window.ws_col - offset) / 2, ' '); }

void UiHandler::alignContentWithOffset(unsigned offsetX, unsigned offsetY) {
  std::cout << std::string((window.ws_row - offsetY) / 2, '\n') << std::string((window.ws_col - offsetX) / 2, ' ');
}
