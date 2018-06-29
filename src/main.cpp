#include <iostream>
#include <string>

using namespace std;

// TODO: system specific!!!
void clearScreen() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    cout << "\x1B[2J\x1B[H";
}

const string readString() {
	string line;
	getline(cin, line);
	
	return line;
}

const int readInteger() {
	const string value = readString();
	return stoi(value);
}

void printHeading() {
	cout << "Groceries Insight" << endl;
	cout << "=================" << endl << endl;
}

void printOptionsMenu() {
	cout << "1. Add Product" << endl;
	
	cout << "Enter your choice: ";
}

void showAddProductRange() {
	cout << "Brand Name:\t";
	string brandName = readString();
	
	cout << "Product Name:\t";
	string productName = readString();
	
	cout << "Barcode:\t";
	int barcode = readInteger();
}

int main(int argc, const char* argv[]) {
	printHeading();
	printOptionsMenu();
	
	int option = readInteger();
	clearScreen();
	
	if (option == 1) {
		showAddProductRange();
	}
}
