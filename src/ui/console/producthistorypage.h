#ifndef PRODUCTHISTORYPAGE_H
#define PRODUCTHISTORYPAGE_H

#include "consolepage.h"

#include "transaction.h"
#include "transactionservice.h"

class ProductHistoryPage : public ConsolePage {
public:
	void show() {
		clearScreen();
		printHeading();
		
		cout << "Product Barcode:\t";
		const int barcode = readInteger();
		cout << "Start Date (YYYY MM DD):\t";
		const time_t startDate = readDate();
		cout << "End Date (YYYY MM DD):\t";
		const time_t endDate = readDate();
		cout << "Sort By:\t";
		const string sortKey = readString();
		cout << endl << endl;
		
		vector<Transaction> allTransactions = TransactionService::getAllTransactions();
		vector<Transaction*> filteredTransactions;
		for (int i = 0; i < allTransactions.size(); ++i) {
			Transaction transaction = allTransactions[i];
			if (transaction.getProduct().getBarcode() != barcode) {
				continue;
			}
			
			if ((transaction.getDate() < startDate) || (transaction.getDate() > endDate)) {
				continue;
			}
			
			filteredTransactions.push_back(&allTransactions[i]);
		}
		
		if (sortKey == "S") {
			sort(filteredTransactions.begin(), filteredTransactions.end(), TransactionComparator::store);
		} else if (sortKey == "P") {
			sort(filteredTransactions.begin(), filteredTransactions.end(), TransactionComparator::price);
		} else {
			sort(filteredTransactions.begin(), filteredTransactions.end(), TransactionComparator::date);
		}

		cout << "Date\t\t" << "Store\t\t" << "Price" << endl;
		int totalPrice = 0;
		int totalTransactions = 0;
		for (Transaction* transaction : filteredTransactions) {
			const time_t date = transaction->getDate();
			struct tm * dateInfo = localtime(&date);
			
			cout << dateInfo->tm_mday << "-" << (dateInfo->tm_mon + 1) << "-" << (dateInfo->tm_year + 1900) << "\t";
			cout << transaction->getStore() << "\t\t";
			cout << transaction->getPrice() << endl;
			
			totalPrice += transaction->getPrice();
			totalTransactions++;
		}
		
		cout << endl;
		cout << "Total Transactions: " << totalTransactions << endl;
		cout << "Total Money Spent: " << totalPrice << endl;
		cout << "Average Price: " << (totalPrice / totalTransactions) << endl;
		
		waitForKey();
	}
};

#endif