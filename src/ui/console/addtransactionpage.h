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

		console.printInputField("Store Name");
		string storeName = console.readString();
		console.printInputField("Date");
		time_t date = console.readDate();

		console.printInputField("Product Barcode");
		int barcode = console.readInteger();
		Product product = ProductService::getProduct(barcode);
		console.printInputField("Product Price");
		int price = console.readInteger();

		Transaction transaction(storeName, date, product, price);
		TransactionService::addTransaction(transaction);
		TransactionService::save();
	}
};

#endif
