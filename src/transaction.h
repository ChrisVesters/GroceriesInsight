#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <time.h>
#include <map>

#include "product.h"

using namespace std;

class Transaction {
public:
	Transaction(const string store, const time_t date, const Product product, const int price);
	
	const string getStore() const;
	const time_t getDate() const;
	const Product getProduct() const;
	const int getPrice() const;
private:
	const string store;
	const time_t date;
	const Product product;
	const int price;
};

#endif