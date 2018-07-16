#include "productservice.h"

TEST(ProductServiceTest, testAddProduct) {
	Product product = new Product(1, "Test", "Example");
	// TODO: we should mock product!!!
	ProductService::addProduct(product);
}

void testAddProductDuplicated() {
	Product product = new Product(2, "Test", "Example");
	ProductService::addProduct(product);
	
	try {
			ProductService::addProduct(product);
	} catch (int e) {
		if (e ==)
	
bool testExistsProductNonExisting() {
	
	return false;
}

bool testExistsProductExisting() {
	for (Product product : products) {
		if (product.getBarcode() == barcode) {
			return true;
		}
	}
	
	return false;
}
	
Product testGetProduct() {
	for (Product product : products) {
		if (product.getBarcode() == barcode) {
			return product;
		}
	}
	
	throw 0;
}