#include <iostream>
#include <string>

#include "product.h"
#include "productservice.h"

using namespace std;

class Console {
public:
	void showMainMenu() {
		clearScreen();
		printHeading();
		
		cout << "1. Add Product" << endl;
		cout << "2. Search Product" << endl;
		cout << "-1. Exit" << endl;

		cout << endl << "Enter your choice: ";
	}
	
	void showAddProductPage() {
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
	}
	
	void showSearchProductPage() {
		clearScreen();
		printHeading();
		
		cout << "Barcode:\t";
		int barcode = readInteger();
		cout << endl;
		
		const Product product = ProductService::getProduct(barcode);
		cout << "Brand Name:\t" << product.getBrand() << endl;
		cout << "Product Name:\t" << product.getName() << endl;
		
		cout << endl << "Press any key to continue";
		waitForKey();
	}
		
	
	static const string readString() {
		string line;
		getline(cin, line);
		
		return line;
	}
	
	static const int readInteger() {
		const string value = readString();
		return stoi(value);
	}
	
private:
	void printHeading() {
		cout << "Groceries Insight" << endl;
		cout << "=================" << endl << endl;
	}

	void clearScreen() {
		// CSI[2J clears screen, CSI[H moves the cursor to top-left corner
		cout << "\x1B[2J\x1B[H";
	}
	
	void waitForKey() {
		cin.get();
	}
};