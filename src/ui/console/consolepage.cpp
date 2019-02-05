#include <iostream>
#include <string>

#include "consolepage.h"

ConsolePage::~ConsolePage() {
}

const string ConsolePage::readString() {
	string line;
	getline(cin, line);
	
	return line;
}

int ConsolePage::readInteger() {
	const string value = readString();
	return stoi(value);
}

time_t ConsolePage::readDate() {
	string yearLiteral;
	string monthLiteral;
	string dayLiteral;
	getline(cin, yearLiteral, ' ');
	getline(cin, monthLiteral, ' ');
	getline(cin, dayLiteral);

	const int year = stoi(yearLiteral);
	const int month = stoi(monthLiteral);
	const int day = stoi(dayLiteral);
			
	struct tm dateInfo = {};
	dateInfo.tm_year = year - 1900;
	dateInfo.tm_mon = month - 1;
	dateInfo.tm_mday = day;
	return mktime(&dateInfo);
}

void ConsolePage::printHeading() {
	cout << "Groceries Insight" << endl;
	cout << "=================" << endl << endl;
}

void ConsolePage::clearScreen() {
	// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
	cout << "\x1B[2J\x1B[H";
}

void ConsolePage::waitForKey(const bool showMessage) {
	if (showMessage) {
		cout << endl << "Press any key to continue";
	}
	cin.get();
}
