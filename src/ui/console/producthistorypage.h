#ifndef PRODUCTHISTORYPAGE_H
#define PRODUCTHISTORYPAGE_H

#include "consolepage.h"

#include "transaction.h"
#include "transactionservice.h"

class ProductHistoryPage : public ConsolePage {
public:
	void show() {
		console.printHeading();
		
		int barcode = stoi(console.printInputField("Product Barcode"));
		const time_t startDate = convertDate(console.printInputField("Start Date"));
		const time_t endDate = convertDate(console.printInputField("End Date"));
		string sortKey = console.printInputField("Sort By");

		
		vector<Transaction> allTransactions = TransactionService::getAllTransactions();
		vector<Transaction*> filteredTransactions;
		for (unsigned int i = 0; i < allTransactions.size(); ++i) {
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

		console.printNewLine(2);
		vector<string> header = {"Date", "Store", "Price"};
		console.printTableHeader(header);

		int totalPrice = 0;
		int totalTransactions = 0;
		for (Transaction* transaction : filteredTransactions) {
			const time_t date = transaction->getDate();
			
			vector<string> row;
			row.push_back(convertDateToString(date));
			row.push_back(transaction->getStore());
			char value[20];
			sprintf(value, "%i", transaction->getPrice());
			row.push_back(value);
			
			totalPrice += transaction->getPrice();
			totalTransactions++;

			console.printTableRow(row);
		}
		console.printNewLine();

		char value[20];
		sprintf(value, "%i", totalTransactions);
		console.printField("Total Transactions", value);

		sprintf(value, "%i", totalPrice);
		console.printField("Total Money Spent", value);

		sprintf(value, "%i", (totalPrice / totalTransactions));
		console.printField("Average Price", value);
		
		console.waitForKey();
	}
};

#endif
