#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"
#define WIPE_SCREEN "\033[2J\033[H"
#define RESET "\033[0m"

namespace ANSI {
    constexpr const char *BLUE = "\033[34m";
    constexpr const char *DODGER_BLUE = "\033[38;5;39m";
    constexpr const char *GREEN = "\033[38;5;114m";
    constexpr const char *LIGHT_GREEN = "\033[32m";

    constexpr const char *RED_UNDERLINE = "\033[4;31m";
} // namespace ANSI

namespace CURSORS {
    constexpr const char *DEFAULT_CURSOR = "\033[47m\033[30m";
} // namespace CURSORS

#endif // !CONSTANTS_HPP
