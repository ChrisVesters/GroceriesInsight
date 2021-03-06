#include "JsonMapper.h"
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

void ProductService::save() {
	DataGatherer gatherer;
	gatherer.startObject("products");
	gatherer.addValue("size", to_string(products.size()));
	
	for (unsigned int i = 0; i < products.size(); ++i) {
		Product product = products[i];
		gatherer.startObject("product-" + to_string(i));
		gatherer.addValue("barcode", to_string(product.getBarcode()));
		gatherer.addValue("brand", product.getBrand());
		gatherer.addValue("name", product.getName());

		UnitSize size = product.getUnitSize();
		gatherer.startObject("UnitSize");
		gatherer.addValue("quantity", to_string(size.getQuantity()));
		gatherer.addValue("unit", size.getUnit());
		gatherer.endObject("UnitSize");

		gatherer.endObject("product-" + to_string(i));
	}
	gatherer.endObject("products");
	
	JsonMapper json("output/products.json");
	json.save(gatherer);
}

void ProductService::load() {
	JsonMapper json("output/products.json");
	DataGatherer gatherer = json.load();

	gatherer.loadObject("products");
	const int size = stoi(gatherer.getValue("size"));
	
	for (int i = 0; i < size; ++i) {
		gatherer.loadObject("product-" + to_string(i));
		const int barcode = stoi(gatherer.getValue("barcode"));
		const string brand = gatherer.getValue("brand");
		const string name = gatherer.getValue("name");

		gatherer.loadObject("UnitSize");
		const long quantity = stoi(gatherer.getValue("quantity"));
		const string unit = gatherer.getValue("unit");
		gatherer.releaseObject("UnitSize");
		gatherer.releaseObject("product-" + to_string(i));
		
		UnitSize size(quantity, unit);
		Product product(barcode, brand, name, size);
		addProduct(product);
		
	}
	gatherer.releaseObject("products");
}
