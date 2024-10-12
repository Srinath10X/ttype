#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

#define GRAY "\033[90m"
#define WHITE "\033[37m"
#define CYAN "\033[36m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define RED "\033[31m"
#define BLACK "\033[30m"
#define RED_UNDERLINE "\033[4;31m"
#define WHITE_BACKGROUND "\033[47m"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define WIPE_SCREEN "\033[2J"
#define RESET "\033[0m"

class TypingTest {
private:
  long long start_time;
  std::string paragraph;
  std::string typed;
  int errors;

public:
  TypingTest() : start_time(0), errors(0) {}

  void run(int word_count);
  void draw_paragraph();
  void generate_paragraph(int count);
  int error_count() const;
  long long millis() const;
  char get_char();        // Method to get single character input
  void display_results(); // Method to display results centered
};

char TypingTest::get_char() {
  struct termios oldt, newt;
  char c;

  // Get current terminal settings
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;

  // Disable canonical mode and echo
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  // Read a single character
  c = getchar();

  // Restore old terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  return c;
}

void TypingTest::run(int word_count) {
  // Hide cursor and clear screen
  std::cout << HIDE_CURSOR;
  system("clear");

  generate_paragraph(word_count); // Generate initial paragraph
  draw_paragraph();               // Draw the initial UI

  while (paragraph.length() > typed.length()) {
    char c = get_char(); // Use custom method for input

    // CTRL + C or CTRL + D to exit
    if (c == 3 || c == 4) {
      std::cout << SHOW_CURSOR;
      return;
    }

    // CTRL + R for reset
    if (c == 18) {
      typed.clear();
      errors = 0;
      start_time = 0;
      generate_paragraph(word_count); // Generate new paragraph
      std::cout << WIPE_SCREEN;       // Clear screen
      draw_paragraph();               // Redraw after reset
      continue;                       // Skip the rest of the loop
    }

    if (start_time <= 0)
      start_time = millis();

    // Handle character input and backspace
    if (c != '\b' && c != 127) { // Normal character input (excluding backspace)
      typed += c;

      if (c != paragraph[typed.length() - 1])
        errors++;
    } else if ((c == '\b' || c == 127) &&
               !typed.empty()) { // Backspace handling for both ASCII DEL and BS
      typed.pop_back();
    }

    draw_paragraph(); // Update display after each character input
  }

  display_results(); // Display the results centered
  std::cout << SHOW_CURSOR;
}

void TypingTest::draw_paragraph() {
  system("clear");
  std::cout << RESET;

  // Get the terminal size
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  unsigned terminal_height = w.ws_row; // Terminal height
  unsigned terminal_width = w.ws_col;  // Terminal width

  // Calculate the total number of newlines available for centering
  int total_lines = terminal_height; // Total lines available in the terminal

  // Calculate 45% of the total newlines for top padding
  int top_padding = static_cast<int>(total_lines * 0.45);

  // Print empty lines for vertical centering (45% at the top)
  for (int i = 0; i < top_padding; ++i) {
    std::cout << std::endl;
  }

  // Calculate spaces needed for centering the paragraph
  int paragraph_length = paragraph.length();
  int total_padding = terminal_width - paragraph_length;

  // Print leading spaces for centering the paragraph
  if (total_padding > 0) {
    int left_padding = total_padding / 2;
    std::cout << std::string(left_padding, ' '); // Add spaces for left padding
  }

  // Draw Typed Paragraph with Color Coding
  for (size_t i = 0; i < typed.length(); i++) {
    if (paragraph[i] == typed[i])
      std::cout << CYAN; // Correct character
    else
      std::cout << RED_UNDERLINE RED; // Incorrect character

    putchar(paragraph[i]);
    std::cout << RESET; // Reset color
  }

  // Fake cursor position indicator
  if (typed.length() < paragraph.length()) {
    std::cout << WHITE_BACKGROUND BLACK;
    putchar(paragraph[typed.length()]);
    std::cout << RESET;
  }

  // Show untapped part of the paragraph in gray color
  for (size_t i = typed.length() + 1; i < paragraph.length(); i++)
    putchar(paragraph[i]);

  std::cout << RESET << std::endl;
}

void TypingTest::generate_paragraph(int count) {
  std::ifstream file("wordlist.txt");

  if (!file.is_open()) {
    throw std::runtime_error("Could not open wordlist.txt");
  }

  std::vector<std::string> words;
  std::string word;

  while (file >> word) {
    words.push_back(word);
  }

  srand(static_cast<unsigned>(time(nullptr)));

  paragraph.clear();

  for (int i = 0; i < count; ++i) {
    paragraph += words[rand() % words.size()] + " ";
  }

  paragraph.pop_back(); // Remove the last space
}

int TypingTest::error_count() const {
  int count = 0;

  for (size_t i = 0; i < paragraph.length(); i++) {
    if (i >= typed.length() || paragraph[i] != typed[i])
      count++;
  }

  return count;
}

long long TypingTest::millis() const {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL; // Convert to milliseconds
}

void TypingTest::display_results() {
  system("clear");
  std::cout << RESET;

  // Print fixed newlines for vertical spacing
  for (int i = 0; i < 10; ++i) { // Adjust the number of lines as needed
    std::cout << std::endl;
  }

  // Display results without special formatting
  system("clear");
  std::cout << "WPM: "
            << (typed.length() / 5.0f) / ((millis() - start_time) / 60000.0f)
            << std::endl;
  std::cout << "Errors: " << error_count() << std::endl;
  std::cout << "Fixed Errors: " << (errors - error_count()) << std::endl;

  // Add padding after results if necessary
  std::cout << std::endl; // Add an extra newline for spacing
}

int main(int argc, char *argv[]) {
  int word_count = (argc == 2 && atoi(argv[1])) ? atoi(argv[1]) : 10;

  TypingTest test;
  test.run(word_count);

  return 0;
}
