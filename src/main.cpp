#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define WIPE_SCREEN "\033[2J"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define RED_UNDERLINE "\033[4;31m"
#define WHITE_BACKGROUND "\033[47m"
#define BLACK "\033[30m"

const vector<string> words = {
    "the",   "of",    "to",    "and",     "a",      "in",    "is",   "it",
    "you",   "that",  "he",    "was",     "for",    "on",    "are",  "with",
    "as",    "I",     "they",  "be",      "at",     "one",   "have", "this",
    "from",  "or",    "by",    "not",     "word",   "but",   "what", "some",
    "we",    "can",   "occur", "support", "nature", "range", "path", "log",
    "meant", "shell", "neck",  "program", "public", "look",  "name", "bee",
};

class TypingTest {
private:
  long long start_time;
  string paragraph;
  string typed;
  int errors;

public:
  TypingTest() : start_time(0), errors(0) {}

  void run(int word_count);
  void draw_paragraph();
  void generate_paragraph(int count);
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

void TypingTest::generate_paragraph(int count) {
  paragraph.clear();
  srand(static_cast<unsigned>(time(nullptr)));
  for (int i = 0; i < count; ++i) {
    paragraph += words[rand() % words.size()] + " ";
  }
  paragraph.pop_back(); // Remove trailing space
}

void TypingTest::draw_paragraph() {
  system("clear");
  cout << RESET;

  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  int top_padding = static_cast<int>(w.ws_row * 0.45);

  for (int i = 0; i < top_padding; ++i) {
    cout << '\n';
  }

  int left_padding = (w.ws_col - paragraph.length()) / 2;
  if (left_padding > 0) {
    cout << string(left_padding, ' ');
  }

  for (size_t i = 0; i < typed.length(); ++i) {
    if (paragraph[i] == typed[i])
      cout << BLUE;
    else
      cout << RED_UNDERLINE;
    cout << paragraph[i] << RESET;
  }

  if (typed.length() < paragraph.length()) {
    cout << WHITE_BACKGROUND BLACK;
    cout << paragraph[typed.length()] << RESET;
  }

  for (size_t i = typed.length() + 1; i < paragraph.length(); ++i) {
    cout << paragraph[i];
  }
  cout << RESET << '\n';
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
  system("clear");
  cout << RESET;

  float minutes = (millis() - start_time) / 60000.0f;
  float wpm = (typed.length() / 5.0f) / minutes;

  cout << "WPM: " << wpm << '\n';
  cout << "Errors: " << error_count() << '\n';
  cout << "Fixed Errors: " << (errors - error_count()) << '\n';
}

void TypingTest::run(int word_count) {
  cout << HIDE_CURSOR;
  generate_paragraph(word_count);
  draw_paragraph();

  while (typed.length() < paragraph.length()) {
    char c = get_char();

    if (c == 3 || c == 4) {
      cout << SHOW_CURSOR;
      return;
    }

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

    if (c != '\b' && c != 127) {
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
  cout << SHOW_CURSOR;
}

int main(int argc, char *argv[]) {
  int word_count = (argc == 2 && atoi(argv[1])) ? atoi(argv[1]) : 10;
  TypingTest test;
  test.run(word_count);
  return 0;
}
