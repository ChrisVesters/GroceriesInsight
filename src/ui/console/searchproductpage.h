#ifndef SEARCHPRODUCTPAGE_H
#define SEARCHPRODUCTPAGE_H

#include "consolepage.h"

#include "product.h"
#include "productservice.h"

class SearchProductPage : public ConsolePage {
public:
	void show() {
		console.printHeading();
		
		console.printInputField("Barcode");
		int barcode = console.readInteger();
		const Product product = ProductService::getProduct(barcode);
		
		console.printField("Brand Name", product.getBrand());
		console.printField("Product Name", product.getName());
		
		console.waitForKey();
	}
};

#endif
