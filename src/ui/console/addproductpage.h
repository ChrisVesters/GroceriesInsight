#ifndef ADDPRODUCTPAGE_H
#define ADDPRODUCTPAGE_H

#include "consolepage.h"

#include "product.h"
#include "productservice.h"

class AddProductPage : public ConsolePage {
public:
	void show() {
		clearScreen();
		printHeading();
		
		cout << "Brand Name:\t";
		string brandName = readString();
		
		cout << "Product Name:\t";
		string productName = readString();
		
		cout << "Barcode:\t";
		int barcode = readInteger();
		
		const Product product(barcode, brandName, productName);
		ProductService::addProduct(product);
		ProductService::save();
	}
};

#endif