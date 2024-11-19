#include "../include/ui_handler.hpp"
#include "../include/constants.hpp"
#include <iostream>
#include <unistd.h>

void UiHandler::wipeAndResetScreen() { std::cout << WIPE_SCREEN RESET; }
void UiHandler::getContext() { ioctl(STDOUT_FILENO, TIOCGWINSZ, &window); }
