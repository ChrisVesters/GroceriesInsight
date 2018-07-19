#include "gtest/gtest.h"
#include "transaction.h"
#include "product.h"

class TransactionTest : public ::testing::Test {
protected:
	
	TransactionTest(): store("Colruyt"), product(123, "Test", "Case"), price(105) {
		time(&date);
	}
	
	string store;
	time_t date;
	Product product;
	int price;
};

TEST_F(TransactionTest, Constructor) {
	Product product(123, "Test", "Case");
	Transaction testTransaction(store, date, product, price);
}

TEST_F(TransactionTest, ConstructorNullStore) {
		Product product(123, "Test", "Case");

	ASSERT_THROW(Transaction testTransaction(NULL, date, product, price), std::logic_error);
}

TEST_F(TransactionTest, ConstructorEmptyStore) {
		Product product(123, "Test", "Case");

	ASSERT_DEATH(Transaction testTransaction("", date, product, price), "!store.empty()");
}

TEST_F(TransactionTest, GetStore) {
		Product product(123, "Test", "Case");

	Transaction testTransaction(store, date, product, price);
	ASSERT_EQ(store, testTransaction.getStore());
}

TEST_F(TransactionTest, GetDate) {
		Product product(123, "Test", "Case");

	Transaction testTransaction(store, date, product, price);
	ASSERT_EQ(date, testTransaction.getDate());
}

TEST_F(TransactionTest, GetProduct) {
		Product product(123, "Test", "Case");

	Transaction testTransaction(store, date, product, price);
	Product result = testTransaction.getProduct();
	
	ASSERT_EQ(product.getBarcode(), result.getBarcode());
	ASSERT_EQ(product.getBrand(), result.getBrand());
	ASSERT_EQ(product.getName(), result.getName());

}

TEST_F(TransactionTest, GetPrice) {
		Product product(123, "Test", "Case");

	Transaction testTransaction(store, date, product, price);
	ASSERT_EQ(price, testTransaction.getPrice());
}