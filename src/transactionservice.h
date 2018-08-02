#ifndef TRANSACTIONSERVICE_H
#define TRANSACTIONSERVICE_H

#include <vector>

#include "transaction.h"

class TransactionService {
public:
	static void addTransaction(const Transaction transaction);
	
	static vector<Transaction> getAllTransactions();
	
	static void save();
	static void load();
private:
	static vector<Transaction> transactions;
};

#endif