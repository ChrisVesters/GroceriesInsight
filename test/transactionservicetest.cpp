#include "transactionservice.h"
#include "transaction.h"
#include "gtest/gtest.h"


TEST(TransactionServiceTest, AddTransaction) {
	string store = "Colruyt";
	time_t date;
	time(&date);
	Product product(123, "Test", "Case");
	int price = 150;

	Transaction transaction(store, date, product, price);
	// TODO: mock transaction.
	TransactionService::addTransaction(transaction);
}

TEST(TransactionServiceTest, GetTransactionsInitial) {
	ASSERT_EQ(0, TransactionService::getAllTransactions().size());
}

TEST(TransactionServiceTest, GetTransactionsAdded) {
	string store = "Colruyt";
	time_t date;
	time(&date);
	Product product(123, "Test", "Case");
	int price = 150;

	Transaction transaction(store, date, product, price);
	TransactionService::addTransaction(transaction);

	vector<Transaction> transactions = TransactionService::getAllTransactions();
	ASSERT_EQ(1, transactions.size());
	ASSERT_EQ(store, transactions[0].getStore());
	ASSERT_EQ(date, transactions[0].getDate());
	// TODO: compare product.
	// ASSERT_EQ(product, transactions[0].getProduct());
	ASSERT_EQ(price, transactions[0].getPrice());
}

