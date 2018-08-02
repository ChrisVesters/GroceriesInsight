#ifndef PRODUCTSERVICE_H
#define PRODUCTSERVICE_H

#include <vector>

#include "DataGatherer.h"
#include "product.h"

class ProductService {
public:
	static void addProduct(Product product);
	
	static bool existsProduct(const int barcode);
	
	static Product getProduct(const int barcode);
	
	static void save();
	static void load();
private:
	static vector<Product> products;
};

#endif