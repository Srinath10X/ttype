/*--------------------------------------------------------------------*
 |      ______                    _    ______                         |
 |     /_  __/__  _________ ___  (_)  /_  __/_  ______  ___           |
 |      / / / _ \/ ___/ __ `__ \/ /    / / / / / / __ \/ _ \          |
 |     / / /  __/ /  / / / / / / /    / / / /_/ / /_/ /  __/          |
 |    /_/  \___/_/  /_/ /_/ /_/_/    /_/  \__, / .___/\___/           |
 |                                      /____/_/                      |
 |                                                                    |
 |     TermiType: A terminal-based typing test application            |
 |                       built with C++                               |
 |                                                                    |
 |     License:  GPLV3 (see LICENSE file at the root of the repo)     |
 |     Github :  https://github.com/srinath10x/ttype                  |
 |     Author :  Srinath10X                                           |
 *-------------------------------------------------------------------*/

#include "../include/constants.hpp"
#include "../include/terminal_handler.hpp"
#include <chrono>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <vector>

TerminalHandler terminal;

const std::vector<std::string> words = {
    "the",   "of",    "to",    "and",     "a",      "in",    "is",   "it",
    "you",   "that",  "he",    "was",     "for",    "on",    "are",  "with",
    "as",    "I",     "they",  "be",      "at",     "one",   "have", "this",
    "from",  "or",    "by",    "not",     "word",   "but",   "what", "some",
    "we",    "can",   "occur", "support", "nature", "range", "path", "log",
    "meant", "shell", "neck",  "program", "public", "look",  "name", "bee",
};

struct winsize window;

class TermiType {
private:
  std::string paragraph;
  std::string typed;
  std::chrono::high_resolution_clock::time_point start_time;
  std::chrono::high_resolution_clock::time_point end_time;
  bool timer_started = false;
  unsigned corrected_chars = 0;

public:
  void run(unsigned word_count);
  void generateParagraph(unsigned count);
  void drawParagraph();
  void displayResults();
};

void TermiType::generateParagraph(unsigned count) {
  paragraph.clear();
  for (unsigned i = 0; i < count; ++i) {
    paragraph += words[rand() % words.size()] + " ";
  }
  paragraph.pop_back();
}

void TermiType::drawParagraph() {
  std::cout << WIPE_SCREEN << RESET;

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);

  unsigned top_padding = (window.ws_row - 1) / 2;
  unsigned left_padding = (window.ws_col - paragraph.length()) / 2;

  std::cout << std::string(top_padding, '\n') << std::string(left_padding, ' ');
  for (size_t i = 0; i < typed.length(); ++i) {
    if (paragraph[i] == typed[i])
      std::cout << BLUE;
    else
      std::cout << RED_UNDERLINE;
    std::cout << paragraph[i] << RESET;
  }

  std::cout << WHITE_BACKGROUND BLACK << paragraph[typed.length()] << RESET;

  for (size_t i = typed.length() + 1; i < paragraph.length(); ++i)
    std::cout << paragraph[i];
}

void TermiType::displayResults() {
  std::cout << WIPE_SCREEN << RESET;

  unsigned top_padding = (window.ws_row - 2) / 2;
  std::chrono::duration<double> duration = end_time - start_time;
  double wpm = (typed.length() / 5.0) * (60 / duration.count());
  unsigned accuracy = (corrected_chars * 100) / typed.length();
  unsigned left_padding =
      (window.ws_col - (std::to_string(wpm).length() + 5)) / 2;

  std::cout << std::string(top_padding, '\n') << std::string(left_padding, ' ');
  std::cout << "WPM: " << wpm << std::endl;

  std::cout << std::string(left_padding, ' ') << "Accuracy: " << accuracy << "%"
            << std::endl;
  getchar();
}

void TermiType::run(unsigned word_count) {
  terminal.enableRawMode();
  generateParagraph(word_count);

  while (typed.length() < paragraph.length()) {
    drawParagraph();
    char c = getchar();

    if (!timer_started) {
      start_time = std::chrono::high_resolution_clock::now();
      timer_started = true;
    }

    if (c == 18) {
      typed.clear();
      generateParagraph(word_count);
      timer_started = false;
      corrected_chars = 0;
      continue;
    } else if (c != 127) {
      typed += c;
      if (typed.back() == paragraph[typed.length() - 1])
        corrected_chars++;

    } else if (!typed.empty()) {
      if (typed.back() == paragraph[typed.length() - 1])
        corrected_chars--;
      typed.pop_back();
    }
  }
  end_time = std::chrono::high_resolution_clock::now();

  displayResults();
  terminal.disableRawMode();
}

int main(int argc, char *argv[]) {
  TermiType termi_type;
  signal(SIGINT, terminal.signalHandler);
  srand(static_cast<unsigned>(time(nullptr)));
  termi_type.run(10);
  return 0;
}
