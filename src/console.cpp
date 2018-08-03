#include <iostream>
#include <string>
#include <algorithm>
#include <string.h>

#include "product.h"
#include "productservice.h"
#include "transaction.h"
#include "transactionservice.h"
#include "transactioncomparator.h"

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
		cout << "5. Show Product History" << endl;
		cout << "6. Show Expenditure History" << endl;
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
		TransactionService::save();
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
		
		waitForKey();
	}
	
	void showProductHistoryPage() {
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
	
	void showExpenditureHistoryPage() {
		clearScreen();
		printHeading();
		
		cout << "Start Date (YYYY MM DD):\t";
		const time_t startDate = readDate();
		cout << "End Date (YYYY MM DD):\t";
		const time_t endDate = readDate();
		cout << "Group By:\t";
		const string groupKey = readString();
		cout << endl << endl;
		
		
		struct tm startInfo = *localtime(&startDate);
		struct tm endInfo = *localtime(&endDate);
		
		int intervals = 0;
		if (groupKey == "Y") {
			intervals = (endInfo.tm_year - startInfo.tm_year) + 1; 
		} else { // "M"
			intervals = ((endInfo.tm_year - startInfo.tm_year) * 12) + (endInfo.tm_mon - startInfo.tm_mon) + 1; 
		}
		
		cout << "Store\t\t|";
		for (int i = 0; i < intervals; ++i) {
			cout << i << "\t";
		}
		cout << endl;
		
		vector<Transaction> allTransactions = TransactionService::getAllTransactions();
		vector<Transaction*> filteredTransactions;
		for (int i = 0; i < allTransactions.size(); ++i) {
			Transaction transaction = allTransactions[i];
			
			if ((transaction.getDate() < startDate) || (transaction.getDate() > endDate)) {
				continue;
			}
			
			filteredTransactions.push_back(&allTransactions[i]);
		}
		
		sort(filteredTransactions.begin(), filteredTransactions.end(), TransactionComparator::store);

		string currentStore = filteredTransactions[0]->getStore();
		int expenditures[intervals];
		memset(expenditures, 0, sizeof(expenditures));

		int totalPrice = 0;
		int totalTransactions = 0;
		for (Transaction* transaction : filteredTransactions) {
			if (transaction->getStore() != currentStore) {
				// Print accumulated results + reset;
				cout << currentStore << "\t\t|";
				for (int i = 0; i < intervals; ++i) {
					cout << expenditures[i] << "\t";
				}
				cout << endl;
				
				currentStore = transaction->getStore();
				memset(expenditures, 0, sizeof(expenditures));
			}
			
			const time_t transactionTime = transaction->getDate();
			struct tm transInfo = *localtime(&transactionTime);
			
			if (groupKey == "Y") {
				const int interval = (transInfo.tm_year - startInfo.tm_year);
				expenditures[interval] += transaction->getPrice();
			} else { // "M"
				const int interval = ((transInfo.tm_year - startInfo.tm_year) * 12) + (transInfo.tm_mon - startInfo.tm_mon); 
				expenditures[interval] += transaction->getPrice();
			}
			
			totalPrice += transaction->getPrice();
			++totalTransactions;
		}
		
		// Print last store!
		cout << currentStore << "\t\t|";
		for (int i = 0; i < intervals; ++i) {
			cout << expenditures[i] << "\t";
		}
		cout << endl;
		
		cout << endl;
		cout << "Total Transactions: " << totalTransactions << endl;
		cout << "Total Money Spent: " << totalPrice << endl;
		cout << "Average Spent: " << (totalPrice / totalTransactions) << endl;

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
	
	static const time_t readDate() {
		string yearLiteral;
		string monthLiteral;
		string dayLiteral;
		getline(cin, yearLiteral, ' ');
		getline(cin, monthLiteral, ' ');
		getline(cin, dayLiteral);

		const int year = stoi(yearLiteral);
		const int month = stoi(monthLiteral);
		const int day = stoi(dayLiteral);
				
		struct tm dateInfo = {};
		dateInfo.tm_year = year - 1900;
		dateInfo.tm_mon = month - 1;
		dateInfo.tm_mday = day;
		return mktime(&dateInfo);
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
	
	void waitForKey(const bool showMessage = true) {
		if (showMessage) {
			cout << endl << "Press any key to continue";
		}
		cin.get();
	}
};