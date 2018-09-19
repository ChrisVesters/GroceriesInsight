#ifndef ALLTRANSACTIONSPAGE_H
#define ALLTRANSACTIONSPAGE_H

#include "consolepage.h"

#include "product.h"
#include "transaction.h"
#include "transactionservice.h"

class AllTransactionsPage : public ConsolePage {
public:
	void show() {
		clearScreen();
		printHeading();
		
		cout << "Date\t\t" << "Store\t" << "\t\tProduct\t\t\t" << "Price" << endl;
		for (const Transaction transaction : TransactionService::getAllTransactions()) {
			const time_t date = transaction.getDate();
			struct tm * dateInfo = localtime(&date);
			Product product = transaction.getProduct();
			
			cout << dateInfo->tm_mday << "-" << (dateInfo->tm_mon + 1) << "-" << (dateInfo->tm_year + 1900) << "\t";
			cout << transaction.getStore() << "\t\t";
			cout << product.getBrand() << " - " << product.getName() << "\t\t";
			cout << transaction.getPrice() << endl;
		}
		
		waitForKey();
	}
};

#endif