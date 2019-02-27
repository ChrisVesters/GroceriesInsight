#include <iostream>
#include <string>

#include "consolepage.h"

Console ConsolePage::console;

ConsolePage::~ConsolePage() {
}

string ConsolePage::convertDateToString(time_t date) {
	struct tm * dateInfo = localtime(&date);
	char dateString[12];
	sprintf(dateString, "%2i/%2i/%4i", dateInfo->tm_mday, (dateInfo->tm_mon + 1), (dateInfo->tm_year + 1900));
	return string(dateString);
}
