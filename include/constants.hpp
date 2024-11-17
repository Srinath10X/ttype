#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <vector>

const std::vector<std::string> words = {
    "the",   "of",    "to",    "and",     "a",      "in",    "is",   "it",
    "you",   "that",  "he",    "was",     "for",    "on",    "are",  "with",
    "as",    "I",     "they",  "be",      "at",     "one",   "have", "this",
    "from",  "or",    "by",    "not",     "word",   "but",   "what", "some",
    "we",    "can",   "occur", "support", "nature", "range", "path", "log",
    "meant", "shell", "neck",  "program", "public", "look",  "name", "bee",
};

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define WIPE_SCREEN "\033[2J\033[H"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define RED_UNDERLINE "\033[4;31m"
#define WHITE_BACKGROUND "\033[47m"
#define BLACK "\033[30m"

#endif // !CONSTANTS_HPP
