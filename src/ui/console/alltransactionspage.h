#ifndef ALLTRANSACTIONSPAGE_H
#define ALLTRANSACTIONSPAGE_H

#include "consolepage.h"

#include "product.h"
#include "transaction.h"
#include "transactionservice.h"

class AllTransactionsPage: public ConsolePage {
public:
	void show() {
		console.printHeading();

		vector<string> header = {"Date", "Store", "Brand", "Name", "Price"};
		console.printTableHeader(header);

		for (const Transaction transaction : TransactionService::getAllTransactions()) {
			const time_t date = transaction.getDate();
			Product product = transaction.getProduct();

			vector<string> row;
			string dateString = convertDateToString(date);
			row.push_back(dateString);
			row.push_back(transaction.getStore());
			row.push_back(product.getBrand());
			row.push_back(product.getName());
			char price[20];
			sprintf(price, "%i", transaction.getPrice());
			row.push_back(price);
			console.printTableRow(row);
		}

		console.waitForKey();
	}
};

#endif
