#ifndef SRC_UI_CONSOLE_CONSOLE_H_
#define SRC_UI_CONSOLE_CONSOLE_H_

#include <curses.h>
#include <iostream>
#include <string.h>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

// TODO: split the actual screen into different parts.
class Console {
public:
	Console() {
		keypad(main, TRUE);
	}

	void printHeading() {
		clearScreen();
		const std::string title = "Groceries Insight";
		// TODO: handle any problems!!!
		mvaddstr(0, 0, title.c_str());
		mvhline(1, 0, ACS_HLINE, title.length());
		move(3, 0);
		refresh();
	}

	void clearScreen() {
		erase();
	}

	int printSelectionList(const std::vector<std::string> options,
			const unsigned int defaultOption = 0) {
		// TODO: list can not be empty!!!
		noecho();

		int originY;
		int originX;
		getyx(main, originY, originX);
		unsigned int selected = defaultOption;

		int y = originY;
		for (unsigned int i = 0; i < options.size(); ++i) {
			mvaddstr(y++, 0, "[ ] ");
			addstr(options[i].c_str());
		}
		mvaddstr(y + 1, 0, "Press Backspace to Exit");
		mvaddstr(originY + selected, 1, "*");
		refresh();

		// Wait until the user makes a selection
		int keypress;
		while (true) {
			keypress = getch();
			mvaddstr(originY + selected, 1, " ");

			switch (keypress) {
			case KEY_UP:
				if (selected > 0) {
					selected--;
				}
				break;
			case KEY_DOWN:
				if (selected < options.size() - 1) {
					selected++;
				}
				break;
			case 10:
			case 13:
				return selected;
			case KEY_BACKSPACE:
				// TODO: make an exception out of this instead of -1
				return -1;
			}

			mvaddstr(originY + selected, 1, "*");
			refresh();
		}

		return selected;
	}

	// TODO: show all input fields at once!!!
	std::string printInputField(std::string label) {
		echo();
		addstr(label.c_str());
		addstr(":");

		int originY;
		int originX;
		getyx(main, originY, originX);
		move(originY, 20);
		refresh();

		char buffer[100];
		getnstr(buffer, 100);

		return std::string(buffer);
	}

	void printField(std::string label, std::string value) {
		// TODO: find a better solution.
		noecho();
		addstr(label.c_str());
		addstr(":");

		int originY;
		int originX;
		getyx(main, originY, originX);
		move(originY, 20);
		addstr(value.c_str());
		move(originY + 1, 0);
		refresh();
	}

	void printTableHeader(std::vector<std::string> header) {
		noecho();
		int y;
		int x;
		getyx(main, y, x);
		// Each column is 14 pixels wide, where the header is allowed to be at most 12 pixels.
		for (unsigned int i = 0; i < header.size(); ++i) {
			std::string name = header[i];
			mvaddnstr(y, i * 14, name.c_str(), 12);
		}
		mvhline(y + 1, 0, ACS_HLINE, header.size() * 14);
		move(y + 2, 0);
		refresh();
	}

	void printTableRow(std::vector<std::string> row) {
		noecho();
		int y;
		int x;
		getyx(main, y, x);
		// Each column is 14 pixels wide, where the header is allowed to be at most 12 pixels.
		for (unsigned int i = 0; i < row.size(); ++i) {
			std::string name = row[i];
			mvaddnstr(y, i * 14, name.c_str(), 12);
		}
		move(y + 1, 0);
		refresh();
	}

	void printNewLine(unsigned int amount = 1) {
		int y;
		int x;
		getyx(main, y, x);
		move(y + amount, 0);
		refresh();
	}


	void waitForKey(bool showMessage = true) {
		if (showMessage) {
			int y;
			int x;
			getyx(main, y, x);
			mvaddstr(y + 1, 0, "Press any key to continue");
		}
		getch();
	}

	~Console() {
		delwin(main);
		endwin();
	}
private:
	WINDOW* main = initscr();
};

#endif /* SRC_UI_CONSOLE_CONSOLE_H_ */
