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
			console.printHeading();
			
			vector<string> options;
			options.push_back("Add Product");
			options.push_back("Search Product");
			options.push_back("Add Transaction");
			options.push_back("List All Transactions");
			options.push_back("Show Product History");
			options.push_back("Show Expenditure History");

			option = console.printSelectionList(options);
			if (option >= 0 && option < pages.size()) {
				pages[option]->show();
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
