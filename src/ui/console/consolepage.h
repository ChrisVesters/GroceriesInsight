#ifndef CONSOLEPAGE_H
#define CONSOLEPAGE_H

#include <string>

using namespace std;

class ConsolePage {
public:
	virtual void show() = 0;
	virtual ~ConsolePage();
protected:
	void printHeading();
	void clearScreen();
	
	const string readString();
	int readInteger();
	time_t readDate();
	
	void waitForKey(const bool showMessage = true);
};

#endif
