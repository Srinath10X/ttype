# TermiType v1.1.0

**TermiType 🚀**: A terminal-based typing test application built with C++. Test and improve your typing speed while enjoying a minimal, distraction-free environment.

## Showcase

![Typing Test Showcase](https://i.imgur.com/mYKjPvL.png)

## Table of Contents

- [Features](#features-)
- [Getting Started](#getting-started-)
- [Prerequisites](#prerequisites)
- [Installation](#installation-)
- [Usage](#usage-)
- [Customization](#customization-)
- [Contributing](#contributing-)
- [License](#license-)
- [Acknowledgments](#acknowledgments-)

## Features 🚀

- **Accurate WPM Calculation:** Measures your Words Per Minute (WPM) and tracks typing errors.
- **Real-Time Feedback:** Live updates with visual cues for correct and incorrect inputs.
- **Minimal Dependencies:** Uses only standard C++ and POSIX functions—no external libraries.
- **Configurable Word Count:** Specify the number of words for each test run.
- **Error Correction Support:** Tracks fixed errors and shows detailed results at the end.

## Getting Started 🛠️

### Prerequisites

- A C++ compiler (e.g., `g++`).
- Works on Linux and MacOS. For Windows, consider using WSL.
- A terminal that supports ANSI escape sequences.

### Installation 💻

#### For Archlinux users
TermiType is available in aur you can use any aur helper to download `ttype`
> Only version 1.0.0 is available in aur. v1.1.0 will be updated soon after a few weeks
```bash
yay -S ttype
```

#### Build it from source

1. Clone the repository to your local machine:
```bash
git clone https://github.com/Srinath10X/ttype.git
cd ttype
```

2. Compile the source and Install confix :

```bash
sudo make install
```

3. Run the program:
```bash
ttype
```

## Usage 📖

- **Start the Test:** Run `ttype` from the terminal, and the paragraph will appear centered on the screen.
- **Restart Test:** Press `Ctrl + R` to reset the paragraph and start a new test.
- **Exit Mid-Test:** Press `Ctrl + C` or `Ctrl + D` to exit at any time.

### Sample Output:
```
WPM: 47
Accuracy: 100%
```

## Customization 🎨

- **Word List:** Modify the `words` list in `main.cpp` to change the words used during the test.
- **Color Themes:** Customize ANSI escape sequences like `BLUE` or `RED_UNDERLINE` in the code for different text styles.
- **Paragraph Length:** Adjust the default word count by modifying the program's logic or passing a parameter when starting the test.

## Contributing 🤝

Have ideas or found a bug? Contributions are welcome! checkout the [CONTRIBUTING](CONTRIBUTING.md) file for more details.

## License 📝

ttype is licensed under the GPLV3 License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments 🙏

- **C++ Community:** For their continuous support and inspiration.
- **Linux Terminal Enthusiasts:** For inspiring the creation of a terminal-based typing app.
- **ANSI Escape Codes:** For providing text styling and cursor control functionality.

Happy Typing! 🚀
