#include "modules/timer.hpp"

void Timer::startTimer() {
	start = std::chrono::high_resolution_clock::now();
	is_started = true;
}

void Timer::stopTimer() {
	if (is_started) {
		end = std::chrono::high_resolution_clock::now();
		is_started = false;
	}
}

double Timer::getDuration() {
	std::chrono::duration<double> duration = end - start;
	return duration.count();
}
