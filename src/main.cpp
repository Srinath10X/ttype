/*--------------------------------------------------------------------*
 |      ______                    _    ______                         |
 |     /_  __/__  _________ ___  (_)  /_  __/_  ______  ___           |
 |      / / / _ \/ ___/ __ `__ \/ /    / / / / / / __ \/ _ \          |
 |     / / /  __/ /  / / / / / / /    / / / /_/ / /_/ /  __/          |
 |    /_/  \___/_/  /_/ /_/ /_/_/    /_/  \__, / .___/\___/           |
 |                                       /____/_/                     |
 |                                                                    |
 |     TermiType: A terminal-based typing test application            |
 |                       built with C++                               |
 |                                                                    |
 |     License:  GPLV3 (see LICENSE file at the root of the repo)     |
 |     Github :  https://github.com/srinath10x/ttype                  |
 |     Author :  Srinath10X                                           |
 *-------------------------------------------------------------------*/

#include <constants.hpp>
#include <handlers/terminal_handler.hpp>
#include <handlers/ui_handler.hpp>
#include <iostream>
#include <modules/text_generator.hpp>
#include <modules/timer.hpp>

TerminalHandler terminal;
Timer timer;
TextGenerator text_generator;
UiHandler ui;

// TODO: Move this class to another file
class TermiType {
private:
	std::string paragraph;
	std::string typed;
	unsigned corrected_chars = 0;

public:
	void run(unsigned word_count);
	void reset(unsigned word_count);
	static void drawParagraph(const std::string paragraph, const std::string typed);
	void displayResults(unsigned word_count);
};

void TermiType::drawParagraph(const std::string paragraph, const std::string typed) {
	ui.wipeAndResetScreen();
	ui.getContext();
	ui.alignContentWithOffset(paragraph.length(), 1);

	for (size_t i = 0; i < typed.length(); ++i) {
		std::cout << (typed[i] == paragraph[i] ? ANSI::BLUE : ANSI::RED_UNDERLINE);
		std::cout << paragraph[i] << RESET;
	}

	std::cout << CURSORS::DEFAULT_CURSOR << paragraph[typed.length()] << RESET;
	std::cout << paragraph.substr(typed.length() + 1);
}

void TermiType::displayResults(unsigned word_count) {
	ui.wipeAndResetScreen();

	double wpm = (typed.length() / 5.0) * (60 / timer.getDuration());
	unsigned accuracy = (corrected_chars * 100) / typed.length();
	double duration = timer.getDuration();

	unsigned left_padding_offset = std::to_string(wpm).length() + 10;
	unsigned top_padding_offset = 3;

	ui.alignContentWithOffset(left_padding_offset, top_padding_offset);
	std::cout << "WPM: " << wpm << std::endl;
	ui.paddingLeftWithOffset(left_padding_offset);
	std::cout << "Accuracy: " << accuracy << "%" << std::endl;
	ui.paddingLeftWithOffset(left_padding_offset);
	std::cout << "Seconds: " << duration << "(s)" << std::endl;

	char c;
	while (true) {
		c = getchar();

		if (c == 27) {
			reset(word_count);
			TermiType::run(word_count);
		} else if (c == 4) {
			break;
		}
	}
}

void TermiType::reset(unsigned word_count) {
	typed.clear();
	paragraph = text_generator.generateParagraph(word_count);
	timer.is_started = false;
	corrected_chars = 0;
}

void TermiType::run(unsigned word_count) {
	terminal.enableRawMode();
	paragraph = text_generator.generateParagraph(word_count);

	while (typed.length() < paragraph.length()) {
		drawParagraph(paragraph, typed);
		char c = getchar();

		if (!timer.is_started) {
			timer.startTimer();
		}

		if (c == 18) {
			reset(word_count);
			continue;
		} else if (c != 127) {
			typed += c;
			if (typed.back() == paragraph[typed.length() - 1]) corrected_chars++;

		} else if (!typed.empty()) {
			if (typed.back() == paragraph[typed.length() - 1]) corrected_chars--;
			typed.pop_back();
		}
	}
	timer.stopTimer();

	displayResults(word_count);
	terminal.disableRawMode();
}

int main(int argc, char *argv[]) {
	TermiType termi_type;
	srand(static_cast<unsigned>(time(nullptr)));
	terminal.registerSignalHandler();
	termi_type.run(10);
	return 0;
}
