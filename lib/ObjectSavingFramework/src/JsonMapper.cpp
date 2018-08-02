#include <fstream>
#include <typeinfo>

#include <iostream>

#include "DataMapper.h"

using namespace std;

// Currently does not really satisfy the Json spec.
class JsonMapper : public DataMapper {
public:
	JsonMapper(const string fileName) : fileName(fileName) {};	

	const DataGatherer load() {
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
	
	void save(const DataGatherer data) {
		ofstream file(fileName);
		
		if (file.is_open()) {
			for (Node * node : data.getRootNodes()) {
				save(&file, node);
			}
		}
	}

private:
	virtual void save(ofstream * file, Node * node, int indent = 0) {
		writeIndent(file, indent);
		
		if (typeid(* node) == typeid(ObjectNode)) {
			writeOpenObject(file, node->getName());
		} else {
			writeKey(file, node->getName());
			writeValue(file, node->getValue());
		}
		
		// TODO: check if there is a next object!
		writeNewLine(file);
		
		if (typeid(* node) == typeid(ObjectNode)) {
			ObjectNode * objectNode = (ObjectNode *) node;
			for (Node * child : objectNode->getChildren()) {
				save(file, child, indent + 1);
			}
			
			writeIndent(file, indent);
			writeCloseObject(file);
			writeNewLine(file);
		}
	}
	
	
	void writeIndent(ofstream* file, int indent) {
		for (int i = 0; i < indent; ++i) {
			*file << "\t";
		}
	}
	
	void writeOpenObject(ofstream* file, string tagName) {
		writeValue(file, tagName);
		*file << ": {";
	}
	
	void writeKey(ofstream * file, string key) {
		writeValue(file, key);
		*file << ": ";
	}
	
	void writeValue(ofstream* file, string value) {
		// TODO: escape certain characters!
		*file << "\"" << value << "\"";
	}
	
	void writeCloseObject(ofstream* file) {
		*file << "}";
	}
	
	void writeNewLine(ofstream* file) {
		*file << endl;
	}
	
	string extractValue(string raw) {
		const size_t start = raw.find("\"") + 1;
		const size_t end = raw.rfind("\"");
		return raw.substr(start, end - start);
	}
		
	const string fileName;
	stack<string> objects;
};