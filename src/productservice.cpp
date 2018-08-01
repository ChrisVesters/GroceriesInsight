#include "JsonMapper.cpp"
#include "productservice.h"

#include <iostream>

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

const string toString(int value) {
	char buffer[10];
	sprintf(buffer, "%d", value);
	return string(buffer);
}

const int fromString(string value) {
	return stoi(value);
}

void ProductService::save() {
	DataGatherer gatherer;
	gatherer.startObject("products");
	gatherer.addValue("size", toString(products.size()));
	
	for (int i = 0; i < products.size(); ++i) {
		Product product = products[i];
		gatherer.startObject("product-" + toString(i));
		gatherer.addValue("barcode", toString(product.getBarcode()));
		gatherer.addValue("brand", product.getBrand());
		gatherer.addValue("name", product.getName());
		gatherer.endObject("product-" + toString(i));
	}
	gatherer.endObject("products");
	
	JsonMapper json("output/products.json");
	json.save(gatherer);
}

void ProductService::load() {
	JsonMapper json("output/products.json");
	DataGatherer gatherer = json.load();

	gatherer.loadObject("products");
	const int size = fromString(gatherer.getValue("size"));
	
	for (int i = 0; i < size; ++i) {
		gatherer.loadObject("product-" + toString(i));
		const int barcode = fromString(gatherer.getValue("barcode"));
		const string brand = gatherer.getValue("brand");
		const string name = gatherer.getValue("name");
		
		Product product(barcode, brand, name);
		addProduct(product);
		
		gatherer.releaseObject("product-" + toString(i));
	}
	gatherer.releaseObject("products");
}