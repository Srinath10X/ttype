#include "modules/text_generator.hpp"

std::string TextGenerator::generateParagraph(unsigned count) {
  paragraph.clear();
  for (unsigned i = 0; i < count; ++i) {
    paragraph += words[rand() % words.size()] + " ";
  }
  paragraph.pop_back();
  return paragraph;
}
