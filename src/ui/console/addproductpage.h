#ifndef ADDPRODUCTPAGE_H
#define ADDPRODUCTPAGE_H

#include "consolepage.h"

#include "product.h"
#include "productservice.h"

class AddProductPage : public ConsolePage {
public:
	void show() {
		console.printHeading();

		string brandName = console.printInputField("Brand Name");
		string productName = console.printInputField("Product Name");
		int barcode = stoi(console.printInputField("Barcode"));

		const Product product(barcode, brandName, productName);
		ProductService::addProduct(product);
		ProductService::save();
	}
};

#endif
