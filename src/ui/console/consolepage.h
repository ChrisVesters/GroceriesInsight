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
	string convertDateToString(time_t date);

	static Console console;
};

#endif
