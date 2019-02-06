#ifndef CONSOLEPAGE_H
#define CONSOLEPAGE_H

#include <string>
#include "console.h"

using namespace std;

class ConsolePage {
public:
	virtual void show() = 0;
	virtual ~ConsolePage();
protected:
	time_t convertDate(string dateString);
	string convertDateToString(time_t date);

	void waitForKey(const bool showMessage = true);

	static Console console;
};

#endif
