#pragma once

#include <string>
#include <vector>

const std::vector<std::string> words = {
    "the",    "of",    "to",   "and",  "a",     "in",    "is",   "it",      "you",    "that", "he",    "was",
    "for",    "on",    "are",  "with", "as",    "I",     "they", "be",      "at",     "one",  "have",  "this",
    "from",   "or",    "by",   "not",  "word",  "but",   "what", "some",    "we",     "can",  "occur", "support",
    "nature", "range", "path", "log",  "meant", "shell", "neck", "program", "public", "look", "name",  "bee",
};

class TextGenerator {
    std::string paragraph;

  public:
    std::string generateParagraph(unsigned count);
};
