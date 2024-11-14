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

#include <csignal>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define WIPE_SCREEN "\033[2J\033[H"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define RED_UNDERLINE "\033[4;31m"
#define WHITE_BACKGROUND "\033[47m"
#define BLACK "\033[30m"

const std::string VERSION = "v1.0.1";

const std::vector<std::string> words = {
    "the",   "of",    "to",    "and",     "a",      "in",    "is",   "it",
    "you",   "that",  "he",    "was",     "for",    "on",    "are",  "with",
    "as",    "I",     "they",  "be",      "at",     "one",   "have", "this",
    "from",  "or",    "by",    "not",     "word",   "but",   "what", "some",
    "we",    "can",   "occur", "support", "nature", "range", "path", "log",
    "meant", "shell", "neck",  "program", "public", "look",  "name", "bee",
};

void disable_raw_mode() {
  struct termios term;
  tcgetattr(STDIN_FILENO, &term);
  term.c_lflag |= (ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void handle_exit(int signal) {
  disable_raw_mode();
  std::cout << WIPE_SCREEN SHOW_CURSOR;
  exit(0);
}

class TypingTest {
private:
  long long start_time;
  std::string paragraph;
  std::string typed;
  int errors;

public:
  TypingTest() : start_time(0), errors(0) {}

  void run(unsigned word_count);
  void draw_paragraph();
  void generate_paragraph(unsigned count);
  void disable_raw_mode();
  char get_char();
  void display_results();
  long long millis() const;
  int error_count() const;
};

char TypingTest::get_char() {
  struct termios oldt, newt;
  char c;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  c = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

void TypingTest::generate_paragraph(unsigned count) {
  paragraph.clear();
  srand(static_cast<unsigned>(time(nullptr)));
  for (unsigned i = 0; i < count; ++i) {
    paragraph += words[rand() % words.size()] + " ";
  }
  paragraph.pop_back(); // Remove trailing space
}

void TypingTest::draw_paragraph() {
  std::cout << WIPE_SCREEN RESET;

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  unsigned top_padding = static_cast<unsigned>(w.ws_row * 0.45);
  unsigned left_padding =
      static_cast<unsigned>((w.ws_col - paragraph.length()) / 2);

  std::cout << std::string(top_padding, '\n');
  std::cout << std::string(left_padding, ' ');

  for (size_t i = 0; i < typed.length(); ++i) {
    if (paragraph[i] == typed[i])
      std::cout << BLUE;
    else
      std::cout << RED_UNDERLINE;
    std::cout << paragraph[i] << RESET;
  }

  if (typed.length() < paragraph.length()) {
    std::cout << WHITE_BACKGROUND BLACK;
    std::cout << paragraph[typed.length()] << RESET;
  }

  for (size_t i = typed.length() + 1; i < paragraph.length(); ++i) {
    std::cout << paragraph[i];
  }
  std::cout << RESET << '\n';
}

long long TypingTest::millis() const {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

int TypingTest::error_count() const {
  int count = 0;
  for (size_t i = 0; i < paragraph.length(); ++i) {
    if (i >= typed.length() || paragraph[i] != typed[i]) {
      ++count;
    }
  }
  return count;
}

void TypingTest::display_results() {
  std::cout << WIPE_SCREEN << RESET;

  float minutes = (millis() - start_time) / 60000.0f;
  float wpm = (typed.length() / 5.0f) / minutes;

  std::cout << "WPM: " << wpm << '\n';
  std::cout << "Errors: " << error_count() << '\n';
  std::cout << "Fixed Errors: " << (errors - error_count()) << '\n';
}

void TypingTest::run(unsigned word_count) {
  std::cout << HIDE_CURSOR;
  generate_paragraph(word_count);
  draw_paragraph();

  while (typed.length() < paragraph.length()) {
    char c = get_char();

    if (c == 18) {
      typed.clear();
      errors = 0;
      start_time = 0;
      generate_paragraph(word_count);
      draw_paragraph();
      continue;
    }

    if (start_time <= 0) {
      start_time = millis();
    }

    if (c != 127) {
      typed += c;
      if (c != paragraph[typed.length() - 1]) {
        ++errors;
      }
    } else if (!typed.empty()) {
      typed.pop_back();
    }

    draw_paragraph();
  }

  display_results();
  std::cout << SHOW_CURSOR;
}

int main(int argc, char *argv[]) {
  signal(SIGINT, handle_exit);
  int word_count = (argc == 2 && atoi(argv[1])) ? atoi(argv[1]) : 10;
  TypingTest test;
  test.run(word_count);
  return 0;
}
