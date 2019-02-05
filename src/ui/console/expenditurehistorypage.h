#ifndef EXPENDITUREHISTORYPAGE_H
#define EXPENDITUREHISTORYPAGE_H

#include <algorithm>
#include <string.h>

#include "consolepage.h"

#include "transaction.h"
#include "transactionservice.h"
#include "transactioncomparator.h"

class ExpenditureHistoryPage : public ConsolePage {
public:
	void show() {
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
		for (unsigned int i = 0; i < allTransactions.size(); ++i) {
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
};

#endif
