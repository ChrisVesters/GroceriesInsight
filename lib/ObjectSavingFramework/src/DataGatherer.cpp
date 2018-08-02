#include <assert.h>
#include "DataGatherer.h"

void DataGatherer::startObject(string name) {
	assert(!name.empty());
	
	ObjectNode * node = new ObjectNode(name);
	
	// TODO: better to add the node when it is popped?
	if (currentStack.empty()) {
		rootNodes.push_back(node);
	} else {
		currentStack.top()->addChild(node);
	}
	
	currentStack.push(node);
}

void DataGatherer::endObject(string name) {
	assert(!name.empty());
	assert(currentStack.top()->getName() == name);
	
	currentStack.pop();
}

void DataGatherer::addValue(string name, string value) {
	currentStack.top()->addValue(name, value);
}

void DataGatherer::loadObject(const string name) {
	if (currentStack.empty()) {
		// Load from root nodes
		for (ObjectNode * node : rootNodes) {
			if (node->getName() == name) {
				currentStack.push(node);
				return;
			}
		}
	} else {
		Node * node = currentStack.top()->getChild(name);
		currentStack.push((ObjectNode *) node);
	}
}

void DataGatherer::releaseObject(const string name) {
	assert(!name.empty());
	assert(currentStack.top()->getName() == name);
	
	currentStack.pop();
}

string DataGatherer::getValue(const string name) {
	assert(!name.empty());
	return currentStack.top()->getValue(name);
}

vector<ObjectNode *> DataGatherer::getRootNodes() const {
	assert(currentStack.empty());
	
	return rootNodes;
}