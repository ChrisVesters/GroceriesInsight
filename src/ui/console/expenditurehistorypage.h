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
		console.printHeading();
		
		const time_t startDate = convertDate(console.printInputField("Start Date"));
		const time_t endDate = convertDate(console.printInputField("End Date"));
		string groupKey = console.printInputField("Group By");
		console.printNewLine(2);
		
		
		struct tm startInfo = *localtime(&startDate);
		struct tm endInfo = *localtime(&endDate);
		
		int intervals = 0;
		if (groupKey == "Y") {
			intervals = (endInfo.tm_year - startInfo.tm_year) + 1; 
		} else { // "M"
			intervals = ((endInfo.tm_year - startInfo.tm_year) * 12) + (endInfo.tm_mon - startInfo.tm_mon) + 1; 
		}
		
		vector<string> header;
		header.push_back("Store");
		for (int i = 0; i < intervals; ++i) {
			char value[20];
			sprintf(value, "%i", i);
			header.push_back(value);
		}
		console.printTableHeader(header);
		
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
				vector<string> row;
				row.push_back(currentStore);
				// Print accumulated results + reset;
				for (int i = 0; i < intervals; ++i) {
					char value[20];
					sprintf(value, "%i", expenditures[i]);
					row.push_back(value);
				}
				console.printTableRow(row);
				
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
		vector<string> row;
		row.push_back(currentStore);
		for (int i = 0; i < intervals; ++i) {
			char value[20];
			sprintf(value, "%i", expenditures[i]);
			row.push_back(value);
		}
		console.printTableRow(row);
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
