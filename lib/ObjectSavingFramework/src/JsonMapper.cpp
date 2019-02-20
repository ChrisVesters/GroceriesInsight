#include <typeinfo>
#include "JsonMapper.h"

using namespace std;

JsonMapper::JsonMapper(const string fileName) :
		fileName(fileName) {
};

const DataGatherer JsonMapper::load() {
	DataGatherer gatherer;
	ifstream file(fileName);

	if (file.is_open()) {
		string line;
		while (getline(file, line)) {
			size_t separator = line.find(":");
			if (separator != string::npos) {
				const string key = line.substr(0, separator);
				const string value = line.substr(separator + 1);
				if (value.find("{") != string::npos) {
					const string objectName = extractValue(key);
					gatherer.startObject(objectName);
					objects.push(objectName);
				} else {
					gatherer.addValue(extractValue(key), extractValue(value));
				}
			} else {
				// Empty line, or closing line of some sort!
				string key = objects.top();
				gatherer.endObject(key);
				objects.pop();
			}
		}

		file.close();
	}

	return gatherer;
}

void JsonMapper::save(const DataGatherer data) {
	ofstream file(fileName);

	if (file.is_open()) {
		for (Node * node : data.getRootNodes()) {
			save(&file, node);
		}
	}
}

void JsonMapper::save(ofstream * file, Node * node, int indent) {
	writeIndent(file, indent);

	if (typeid(*node) == typeid(ObjectNode)) {
		writeOpenObject(file, node->getName());
	} else {
		writeKey(file, node->getName());
		writeValue(file, node->getValue());
	}

	// TODO: check if there is a next object!
	writeNewLine(file);

	if (typeid(*node) == typeid(ObjectNode)) {
		ObjectNode * objectNode = (ObjectNode *) node;
		for (Node * child : objectNode->getChildren()) {
			save(file, child, indent + 1);
		}

		writeIndent(file, indent);
		writeCloseObject(file);
		writeNewLine(file);
	}
}

void JsonMapper::writeIndent(ofstream* file, int indent) {
	for (int i = 0; i < indent; ++i) {
		*file << "\t";
	}
}

void JsonMapper::writeOpenObject(ofstream* file, string tagName) {
	writeValue(file, tagName);
	*file << ": {";
}

void JsonMapper::writeKey(ofstream * file, string key) {
	writeValue(file, key);
	*file << ": ";
}

void JsonMapper::writeValue(ofstream* file, string value) {
	// TODO: escape certain characters!
	*file << "\"" << value << "\"";
}

void JsonMapper::writeCloseObject(ofstream* file) {
	*file << "}";
}

void JsonMapper::writeNewLine(ofstream* file) {
	*file << endl;
}

string JsonMapper::extractValue(string raw) {
	const size_t start = raw.find("\"") + 1;
	const size_t end = raw.rfind("\"");
	return raw.substr(start, end - start);
}
