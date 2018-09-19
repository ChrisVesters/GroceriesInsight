#ifndef ADDTRANSACTIONPAGE_H
#define ADDTRANSACTIONPAGE_H

#include "consolepage.h"

#include "product.h"
#include "productservice.h"
#include "transaction.h"
#include "transactionservice.h"

class AddTransactionPage : public ConsolePage {
public:
	void show() {
		clearScreen();
		printHeading();
		
		cout << "Store Name:\t\t";
		string storeName = readString();
		
		cout << "Date" << endl;
		cout << "\tDay:\t";
		int day = readInteger();
		cout << "\tMonth:\t" ;
		int month = readInteger();
		cout << "\tYear:\t";
		int year = readInteger();
		
		struct tm dateInfo = {};
		dateInfo.tm_year = year - 1900;
		dateInfo.tm_mon = month - 1;
		dateInfo.tm_mday = day;
		time_t date = mktime(&dateInfo);
		
		cout << "Product Barcode:\t";
		Product product = ProductService::getProduct(readInteger());		
		
		cout << "Product Price:\t\t";
		int price = readInteger();
		
		Transaction transaction(storeName, date, product, price);
		TransactionService::addTransaction(transaction);
		TransactionService::save();
	}
};

#endif