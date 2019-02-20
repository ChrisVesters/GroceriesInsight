#include "ConsoleMapper.h"

const DataGatherer ConsoleMapper::load() {
	return DataGatherer();
}

void ConsoleMapper::save(const DataGatherer data) {
	for (Node * node : data.getRootNodes()) {
		print(node);
	}
}

void ConsoleMapper::print(const Node * node, int indent) {
	for (int i = 0; i < indent; ++i) {
		cout << "\t";
	};

	cout << node->getName() << " = " << node->getValue() << endl;

	vector<Node *> children = node->getChildren();
	for (Node* node : children) {
		print(node, indent + 1);
	}
}
