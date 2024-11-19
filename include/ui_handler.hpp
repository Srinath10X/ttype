#ifndef UI_HANDLER_HPP
#define UI_HANDLER_HPP

#include <sys/ioctl.h>

class UiHandler {
public:
  struct winsize window;
  void getContext();
  void wipeAndResetScreen();
};

#endif // !UI_HANDLER_HPP
