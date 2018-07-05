#include <iostream>
#include <string>
#include "console.cpp"

using namespace std;

class GroceriesInsight {
public:
	GroceriesInsight() {
		console;
	}
	
	void run() {
		int option;
		do {
			console.showMainMenu();
			
			option = Console::readInteger();
			switch (option) {
				case 1:
					console.showAddProductPage();
					break;
				case 2:
					console.showSearchProductPage();
					break;
				default:
					break;
			}
		} while (option != -1);
	}
private:
	Console console;
};

int main(int argc, const char* argv[]) {
	GroceriesInsight application;
	application.run();
}
