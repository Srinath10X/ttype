#ifndef UI_HANDLER_HPP
#define UI_HANDLER_HPP

#include <sys/ioctl.h>

class UiHandler {
public:
  struct winsize window;

  void getContext();
  void wipeAndResetScreen();
  void paddingTop(unsigned offset);
  void paddingLeft(unsigned offset);
  void alignContentWithOffset(unsigned offsetX, unsigned offsetY);
};

#endif // !UI_HANDLER_HPP
