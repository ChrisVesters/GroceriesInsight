#ifndef MAINMENU_H
#define MAINMENU_H

#include "consolepage.h"

#include "addproductpage.h"
#include "addtransactionpage.h"
#include "alltransactionspage.h"
#include "expenditurehistorypage.h"
#include "producthistorypage.h"
#include "searchproductpage.h"

class MainMenu : public ConsolePage {
public:
	MainMenu() {
		pages.push_back(new AddProductPage);
		pages.push_back(new SearchProductPage);
		pages.push_back(new AddTransactionPage);
		pages.push_back(new AllTransactionsPage);
		pages.push_back(new ProductHistoryPage);
		pages.push_back(new ExpenditureHistoryPage);
	}

	void show() {
		int option;
		do {
			clearScreen();
			printHeading();
			
			cout << "1. Add Product" << endl;
			cout << "2. Search Product" << endl;
			cout << "3. Add Transaction" << endl;
			cout << "4. List All Transactions" << endl;
			cout << "5. Show Product History" << endl;
			cout << "6. Show Expenditure History" << endl;
			cout << "-1. Exit" << endl;

			cout << endl << "Enter your choice: ";
			option = readInteger();
			if ((option < 0) || (option > pages.size())) {
				// todo: invalid!!!
			} else {
				pages[option - 1]->show();
			}
		} while (option != -1);
	}
	
	~MainMenu() {
		// TODO: delete all pages again.
		while (!pages.empty()) {
			delete pages.back();
			pages.pop_back();
		}
	}

private:
	vector<ConsolePage *> pages;
};

#endif