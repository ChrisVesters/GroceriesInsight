#include <iostream>
#include <string>

#include "productservice.h"
#include "transactionservice.h"

#include "ui/console/mainmenu.h"

using namespace std;

int main(int argc, const char* argv[]) {
	ProductService::load();
	TransactionService::load();
	
	MainMenu menu;
	menu.show();
}
