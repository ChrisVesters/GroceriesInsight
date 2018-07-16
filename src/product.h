#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product {
public:
	Product(const int barcode, const string brand, const string name);
	
	const int getBarcode() const;
	const string getBrand() const;
	const string getName() const;
private:
	const int barcode;
	const string brand;
	const string name;
};

#endif