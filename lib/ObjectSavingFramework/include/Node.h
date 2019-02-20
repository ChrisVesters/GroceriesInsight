#ifndef NODE_H
#define NODE_H

#include <vector>
#include <sstream>

using namespace std;

class Node {
public:
	string getName() const {
		return name;
	}

	string getValue() const {
		return getValueString();
	}
	
	virtual vector<Node *> getChildren() const {
		return vector<Node*>();
	}
	
	virtual ~Node() {
	}
protected:
	Node(string name) : name(name) {};
	virtual string getValueString() const = 0;

private:
	const string name;
};

// Some mappers may want to know the type of the field!
class FieldNode : public Node {
public:
	FieldNode(const string name, const string value): Node(name), value(value) {};

protected:
	string getValueString() const {
		return value;
	}
	
private:
	const string value;
};


class ObjectNode : public Node {
public:
	ObjectNode(const string name): Node(name) {}
	
	void addValue(const string name, const string value) {
		childNodes.push_back(new FieldNode(name, value));
	}
	
	void addChild(Node * node) {
		childNodes.push_back(node);
	}
	
	string getValue(const string name) {
		for (Node * node : childNodes) {
			if (node->getName() == name) {
				return node->getValue();
			}
		}

		return nullptr;
	}
	
	Node * getChild(const string name) {
		for (Node * node : childNodes) {
			if (node->getName() == name) {
				return node;
			}
		}

		return nullptr;
	}
	
	vector<Node*> getChildren() const {
		return childNodes;
	}

	~ObjectNode() {
		for (vector<Node *>::iterator it = childNodes.begin(); it != childNodes.end(); ++it) {
			delete *it;
		}
		childNodes.clear();
	}
protected:
	string getValueString() const {
		return string();
	}

private:
	vector<Node *> childNodes;
};

#endif
