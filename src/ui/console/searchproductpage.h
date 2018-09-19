#ifndef SEARCHPRODUCTPAGE_H
#define SEARCHPRODUCTPAGE_H

#include "consolepage.h"

#include "product.h"
#include "productservice.h"

class SearchProductPage : public ConsolePage {
public:
	void show() {
		clearScreen();
		printHeading();
		
		cout << "Barcode:\t";
		int barcode = readInteger();
		cout << endl;
		
		const Product product = ProductService::getProduct(barcode);
		cout << "Brand Name:\t" << product.getBrand() << endl;
		cout << "Product Name:\t" << product.getName() << endl;
		
		waitForKey();
	}
};

#endif