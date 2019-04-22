#include <assert.h>

#include "product.h"

Product::Product(const int barcode, const string brand, const string name, const UnitSize& size) : barcode(barcode), brand(brand), name(name), size(size) {
	assert (!brand.empty());
	assert (!name.empty());
}
	
int Product::getBarcode() const {
	return barcode;
}

const string Product::getBrand() const {
	return brand;
}

const string Product::getName() const {
	return name;
}

const UnitSize Product::getUnitSize() const {
	return size;
}
