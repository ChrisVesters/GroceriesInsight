#include "gtest/gtest.h"
#include "transaction.h"
#include "product.h"

class TransactionTest : public ::testing::Test {
protected:

	
	TransactionTest(): store("Colruyt"), unit(100, "g"), product(123, "Test", "Case", unit), price(105) {
		time(&date);
	}
	
	string store;
	time_t date;
	UnitSize unit;
	Product product;
	int price;
};

TEST_F(TransactionTest, Constructor) {
	Transaction testTransaction(store, date, product, price);
}

TEST_F(TransactionTest, ConstructorNullStore) {
	ASSERT_THROW(Transaction testTransaction(NULL, date, product, price), std::logic_error);
}

TEST_F(TransactionTest, ConstructorEmptyStore) {
	ASSERT_DEATH(Transaction testTransaction("", date, product, price), "!store.empty()");
}

TEST_F(TransactionTest, GetStore) {
	Transaction testTransaction(store, date, product, price);
	ASSERT_EQ(store, testTransaction.getStore());
}

TEST_F(TransactionTest, GetDate) {
	Transaction testTransaction(store, date, product, price);
	ASSERT_EQ(date, testTransaction.getDate());
}

TEST_F(TransactionTest, GetProduct) {
	Transaction testTransaction(store, date, product, price);
	Product result = testTransaction.getProduct();
	
	ASSERT_EQ(product.getBarcode(), result.getBarcode());
	ASSERT_EQ(product.getBrand(), result.getBrand());
	ASSERT_EQ(product.getName(), result.getName());

}

TEST_F(TransactionTest, GetPrice) {
	Transaction testTransaction(store, date, product, price);
	ASSERT_EQ(price, testTransaction.getPrice());
}
