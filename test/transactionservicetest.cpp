#include "transactionservice.h"
#include "transaction.h"
#include "gtest/gtest.h"

class TransactionServiceTest : public ::testing::Test {
protected:

};

TEST_F(TransactionServiceTest, AddTransaction) {
	string store = "Colruyt";
	time_t date;
	time(&date);
	Product product(123, "Test", "Case");
	int price = 150;

		
		
	Transaction transaction(store, date, product, price);
	TransactionService::addTransaction(transaction);
}

TEST_F(TransactionServiceTest, GetTransactions) {
	ASSERT_EQ(1, TransactionService::getAllTransactions().size());
}