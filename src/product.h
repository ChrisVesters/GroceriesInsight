#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

#include "UnitSize.hpp"

using namespace std;

class Product {
public:
	Product(const int barcode, const string brand, const string name, const UnitSize& size);
	
	int getBarcode() const;
	const string getBrand() const;
	const string getName() const;
	const UnitSize getUnitSize() const;
private:
	const int barcode;
	const string brand;
	const string name;
	const UnitSize size;
};

#endif
