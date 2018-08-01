#include <fstream>
#include <typeinfo>

#include "DataMapper.h"

using namespace std;

class XmlMapper : public DataMapper {
public:
	XmlMapper(const string fileName) : fileName(fileName) {};	

	const DataGatherer load() {
		ifstream file(fileName);
		
		if (file.is_open()) {
			file.close();
		}
		
		return DataGatherer();
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
			writeOpenTag(file, node->getName());
		} else {
			writeOpenTag(file, node->getName());
			writeValue(file, node->getValue());
			writeCloseTag(file, node->getName());
		}
		
		writeNewLine(file);
		
		if (typeid(* node) == typeid(ObjectNode)) {
			ObjectNode * objectNode = (ObjectNode *) node;
			for (Node * child : objectNode->getChildren()) {
				save(file, child, indent + 1);
			}
			writeCloseTag(file, node->getName());
		}
	}
	
	
	void writeIndent(ofstream* file, int indent) {
		for (int i = 0; i < indent; ++i) {
			*file << "\t";
		}
	}
	
	void writeOpenTag(ofstream* file, string tagName) {
		*file << "<";
		writeValue(file, tagName);
		*file << ">";
	}
	
	void writeValue(ofstream* file, string value) {
		// TODO: escape certain characters!
		*file << value;
	}
	
	void writeCloseTag(ofstream* file, string tagName) {
		*file << "</";
		writeValue(file, tagName);
		*file << ">";
	}
	
	void writeNewLine(ofstream* file) {
		*file << endl;
	}
 
	const string fileName;
};