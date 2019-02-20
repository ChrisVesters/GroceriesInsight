#include "JsonMapper.h"
#include "transactionservice.h"
#include "productservice.h"

vector<Transaction> TransactionService::transactions;

void TransactionService::addTransaction(const Transaction transaction) {
	transactions.push_back(transaction);
}
	
vector<Transaction> TransactionService::getAllTransactions() {
	return transactions;
}

void TransactionService::save() {
	DataGatherer gatherer;
	gatherer.startObject("transactions");
	gatherer.addValue("size", to_string(transactions.size()));
	
	for (unsigned int i = 0; i < transactions.size(); ++i) {
		Transaction transaction = transactions[i];
		gatherer.startObject("transaction-" + to_string(i));
		gatherer.addValue("store", transaction.getStore());
		gatherer.addValue("date", to_string(transaction.getDate()));
		gatherer.addValue("product", to_string(transaction.getProduct().getBarcode()));
		gatherer.addValue("price", to_string(transaction.getPrice()));
		gatherer.endObject("transaction-" + to_string(i));
	}
	gatherer.endObject("transactions");
	
	JsonMapper json("output/transactions.json");
	json.save(gatherer);
}

void TransactionService::load() {
	JsonMapper json("output/transactions.json");
	DataGatherer gatherer = json.load();

	gatherer.loadObject("transactions");
	const int size = stoi(gatherer.getValue("size"));
	
	for (int i = 0; i < size; ++i) {
		gatherer.loadObject("transaction-" + to_string(i));
		
		const string store = gatherer.getValue("store");
		const time_t date = stoi(gatherer.getValue("date"));
		const int barcode = stoi(gatherer.getValue("product"));
		const int price = stoi(gatherer.getValue("price"));
		
		Product product = ProductService::getProduct(barcode);
		Transaction transaction(store, date, product, price);
		addTransaction(transaction);
		
		gatherer.releaseObject("transaction-" + to_string(i));
	}
	gatherer.releaseObject("transactions");
}
