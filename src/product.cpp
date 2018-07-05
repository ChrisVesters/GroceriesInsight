#include "product.h"

Product::Product(const int barcode, const string brand, const string name) : barcode(barcode), brand(brand), name(name) {
}
	
const int Product::getBarcode() {
	return barcode;
}

const string Product::getBrand() {
	return brand;
}

const string Product::getName() {
	return name;
}