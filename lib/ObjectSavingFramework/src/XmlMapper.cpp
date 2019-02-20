#include "XmlMapper.h"

using namespace std;

XmlMapper::XmlMapper(const string fileName) :
		fileName(fileName) {
}
;

const DataGatherer XmlMapper::load() {
	ifstream file(fileName);

	if (file.is_open()) {
		file.close();
	}

	return DataGatherer();
}

void XmlMapper::save(const DataGatherer data) {
	ofstream file(fileName);

	if (file.is_open()) {
		for (Node * node : data.getRootNodes()) {
			save(&file, node);
		}
	}
}

void XmlMapper::save(ofstream * file, Node * node, int indent) {
	writeIndent(file, indent);

	if (typeid(*node) == typeid(ObjectNode)) {
		writeOpenTag(file, node->getName());
	} else {
		writeOpenTag(file, node->getName());
		writeValue(file, node->getValue());
		writeCloseTag(file, node->getName());
	}

	writeNewLine(file);

	if (typeid(*node) == typeid(ObjectNode)) {
		ObjectNode * objectNode = (ObjectNode *) node;
		for (Node * child : objectNode->getChildren()) {
			save(file, child, indent + 1);
		}
		writeCloseTag(file, node->getName());
	}
}

void XmlMapper::writeIndent(ofstream* file, int indent) {
	for (int i = 0; i < indent; ++i) {
		*file << "\t";
	}
}

void XmlMapper::writeOpenTag(ofstream* file, string tagName) {
	*file << "<";
	writeValue(file, tagName);
	*file << ">";
}

void XmlMapper::writeValue(ofstream* file, string value) {
	// TODO: escape certain characters!
	*file << value;
}

void XmlMapper::writeCloseTag(ofstream* file, string tagName) {
	*file << "</";
	writeValue(file, tagName);
	*file << ">";
}

void XmlMapper::writeNewLine(ofstream* file) {
	*file << endl;
}

const string fileName;
