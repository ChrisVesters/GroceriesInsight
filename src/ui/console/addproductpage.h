#ifndef ADDPRODUCTPAGE_H
#define ADDPRODUCTPAGE_H

#include "consolepage.h"

#include "product.h"
#include "productservice.h"

class AddProductPage : public ConsolePage {
public:
	void show() {
		console.printHeading();

		console.printInputField("Brand Name");
		string brandName = console.readString();
		console.printInputField("Product Name");
		string productName = console.readString();
		console.printInputField("Quantity");
		int quantity = console.readInteger();
		console.printInputField("Unit");
		string unit = console.readString();
		console.printInputField("Barcode");
		int barcode = console.readInteger();

		const UnitSize size(quantity, unit);
		const Product product(barcode, brandName, productName, size);
		ProductService::addProduct(product);
		ProductService::save();
	}
};

#endif
