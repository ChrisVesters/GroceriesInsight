#include <iostream>
#include <string>

#include "consolepage.h"

Console ConsolePage::console;

ConsolePage::~ConsolePage() {
}

time_t ConsolePage::convertDate(string dateString) {
	// TODO: check for valid string.
	int day = stoi(dateString.substr(0, 2));
	int month = stoi(dateString.substr(3, 2));
	int year = stoi(dateString.substr(6, 4));

	struct tm dateInfo = {};
	dateInfo.tm_year = year - 1900;
	dateInfo.tm_mon = month - 1;
	dateInfo.tm_mday = day;
	return mktime(&dateInfo);
}

string ConsolePage::convertDateToString(time_t date) {
	struct tm * dateInfo = localtime(&date);
	char dateString[12];
	sprintf(dateString, "%2i/%2i/%4i", dateInfo->tm_mday, (dateInfo->tm_mon + 1), (dateInfo->tm_year + 1900));
	return string(dateString);
}

void ConsolePage::waitForKey(const bool showMessage) {
	if (showMessage) {
		cout << endl << "Press any key to continue";
	}
	cin.get();
}
