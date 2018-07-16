#include <assert.h>

#include "product.h"

Product::Product(const int barcode, const string brand, const string name) : barcode(barcode), brand(brand), name(name) {
	assert (!brand.empty());
	assert (!name.empty());
}
	
const int Product::getBarcode() const {
	return barcode;
}

const string Product::getBrand() const {
	return brand;
}

const string Product::getName() const {
	return name;
}