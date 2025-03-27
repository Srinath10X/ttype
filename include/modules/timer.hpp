#pragma once

#include <chrono>

class Timer {
  private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point end;

  public:
    bool is_started = false;

    void startTimer();
    void stopTimer();
    double getDuration();
};
