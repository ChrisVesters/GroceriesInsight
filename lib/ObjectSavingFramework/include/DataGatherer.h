#ifndef DATAGATHERER_H
#define DATAGATHERER_H

#include <string>
#include <map>
#include <stack>

#include "Node.h"

using namespace std;

class DataGatherer {
public:
	// Creation API
	void startObject(const string name);
	void endObject(const string name);
	
	void addValue(const string name, const string value);
	
	// Restoring API
	void loadObject(const string name);
	void releaseObject(const string name);
	string getValue(const string name);
	
	// TODO: a better way to iterate!
	vector<ObjectNode *> getRootNodes() const;
private:
	stack<ObjectNode *> currentStack;
	vector<ObjectNode *> rootNodes;
};

#endif