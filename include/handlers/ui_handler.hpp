#ifndef UI_HANDLER_HPP
#define UI_HANDLER_HPP

#include <sys/ioctl.h>

class UiHandler {
public:
  struct winsize window;

  void getContext();
  void wipeAndResetScreen();
  void paddingTop(unsigned top_padding);
  void paddingLeft(unsigned left_padding);
  void paddingTopWithOffset(unsigned offset);
  void paddingLeftWithOffset(unsigned offset);
  void alignContentWithOffset(unsigned offsetX, unsigned offsetY);
};

#endif // !UI_HANDLER_HPP
