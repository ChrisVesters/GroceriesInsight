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
		ProductService::load();
		
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
				case 3:
					console.showAddTransactionPage();
					break;
				case 4:
					console.showAllTransactionsPage();
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
