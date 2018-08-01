#include <iostream>
#include <string>

#include "product.h"
#include "productservice.h"
#include "transaction.h"
#include "transactionservice.h"

using namespace std;

class Console {
public:
	void showMainMenu() {
		clearScreen();
		printHeading();
		
		cout << "1. Add Product" << endl;
		cout << "2. Search Product" << endl;
		cout << "3. Add Transaction" << endl;
		cout << "4. List All Transactions" << endl;
		cout << "-1. Exit" << endl;

		cout << endl << "Enter your choice: ";
	}
	
	void showAddProductPage() {
		clearScreen();
		printHeading();
		
		cout << "Brand Name:\t";
		string brandName = readString();
		
		cout << "Product Name:\t";
		string productName = readString();
		
		cout << "Barcode:\t";
		int barcode = readInteger();
		
		const Product product(barcode, brandName, productName);
		ProductService::addProduct(product);
		ProductService::save();
	}
	
	void showSearchProductPage() {
		clearScreen();
		printHeading();
		
		cout << "Barcode:\t";
		int barcode = readInteger();
		cout << endl;
		
		const Product product = ProductService::getProduct(barcode);
		cout << "Brand Name:\t" << product.getBrand() << endl;
		cout << "Product Name:\t" << product.getName() << endl;
		
		cout << endl << "Press any key to continue";
		waitForKey();
	}
	
	void showAddTransactionPage() {
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
	}
	
	void showAllTransactionsPage() {
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
		
		cout << endl << "Press any key to continue";
		waitForKey();
	}
	
	
	static const string readString() {
		string line;
		getline(cin, line);
		
		return line;
	}
	
	static const int readInteger() {
		const string value = readString();
		return stoi(value);
	}
	
private:
	void printHeading() {
		cout << "Groceries Insight" << endl;
		cout << "=================" << endl << endl;
	}

	void clearScreen() {
		// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
		cout << "\x1B[2J\x1B[H";
	}
	
	void waitForKey() {
		cin.get();
	}
};