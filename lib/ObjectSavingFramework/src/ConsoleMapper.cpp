#include <iostream>

#include "DataMapper.h"

using namespace std;

class ConsoleMapper : public DataMapper {
public:
	const DataGatherer load() {
		
	}
	
	void save(const DataGatherer data) {
		for (Node * node : data.getRootNodes()) {
			print(node);
		}
	}

private:
	void print(const Node * node, int indent = 0) {
		for (int i = 0; i < indent; ++i) {
			cout << "\t";
		};
		
		cout << node->getName() << " = " << node->getValue() << endl;
		
		vector<Node *> children = node->getChildren();
		for (Node* node : children) {
			print(node, indent + 1);
		}
	}
};