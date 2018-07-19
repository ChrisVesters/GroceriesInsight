#include <assert.h>
#include <iostream>
#include "transaction.h"

Transaction::Transaction(const string store, const time_t date, const Product product, const int price) : store(store), date(date), product(product), price(price) {
	assert(!store.empty());
}

const string Transaction::getStore() const {
	return store;
}

const time_t Transaction::getDate() const {
	return date;
}

const Product Transaction::getProduct() const {
	return product;
}

const int Transaction::getPrice() const {
	return price;
}