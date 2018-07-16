#include "productservice.h"

vector<Product> ProductService::products;

void ProductService::addProduct(Product product) {
	if (existsProduct(product.getBarcode())) {
		throw -1;
	}

	products.push_back(product);
}
	
bool ProductService::existsProduct(const int barcode) {
	for (const Product product : products) {
		if (product.getBarcode() == barcode) {
			return true;
		}
	}
	
	return false;
}
	
Product ProductService::getProduct(const int barcode) {
	for (const Product product : products) {
		if (product.getBarcode() == barcode) {
			return product;
		}
	}
	
	throw -1;
}