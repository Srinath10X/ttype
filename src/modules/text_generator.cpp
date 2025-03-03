#include <modules/text_generator.hpp>

std::string TextGenerator::generateParagraph(unsigned count) {
  paragraph.clear();
  int temp = -1;
  for (unsigned i = 0; i < count; ++i) {
    int random_int = rand() % words.size();
    if (temp == random_int) continue;
    paragraph += words[random_int] + " ";
    temp = random_int;
  }
  paragraph.pop_back();
  return paragraph;
}
