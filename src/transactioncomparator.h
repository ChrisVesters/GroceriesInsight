#ifndef TRANSACTION_COMPARATOR
#define TRANSACTION_COMPARATOR

#include "transaction.h"

struct TransactionComparator {
	static bool date(const Transaction* left, const Transaction* right) {
		return left->getDate() < right->getDate();
	}
	
	static bool price(const Transaction* left, const Transaction* right) {
		return left->getPrice() < right->getPrice();
	}
	
	static bool store(const Transaction* left, const Transaction* right) {
		return left->getStore() < right->getStore();
	}
};

#endif