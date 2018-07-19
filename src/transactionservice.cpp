#include "transactionservice.h"

vector<Transaction> TransactionService::transactions;

void TransactionService::addTransaction(const Transaction transaction) {
	transactions.push_back(transaction);
}
	
vector<Transaction> TransactionService::getAllTransactions() {
	return transactions;
}