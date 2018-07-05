#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product {
public:
	Product(const int barcode, const string brand, const string name);
	
	const int getBarcode();
	const string getBrand();
	const string getName();
private:
	const int barcode;
	const string brand;
	const string name;
};

#endif