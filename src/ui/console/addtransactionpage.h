#ifndef ADDTRANSACTIONPAGE_H
#define ADDTRANSACTIONPAGE_H

#include "consolepage.h"

#include "product.h"
#include "productservice.h"
#include "transaction.h"
#include "transactionservice.h"

class AddTransactionPage: public ConsolePage {
public:
	void show() {
		console.printHeading();

		string storeName = console.printInputField("Store Name");
		string dateString = console.printInputField("Date");
		time_t date = convertDate(dateString);

		int barcode = stoi(console.printInputField("Product Barcode"));
		Product product = ProductService::getProduct(barcode);
		int price = stoi(console.printInputField("Product Price"));

		Transaction transaction(storeName, date, product, price);
		TransactionService::addTransaction(transaction);
		TransactionService::save();
	}
};

#endif
