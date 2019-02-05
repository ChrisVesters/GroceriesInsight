#include <iostream>
#include <string>

#include "productservice.h"
#include "transactionservice.h"

#include "ui/console/mainmenu.h"

using namespace std;

int main() {
	ProductService::load();
	TransactionService::load();
	
	MainMenu menu;
	menu.show();
}
