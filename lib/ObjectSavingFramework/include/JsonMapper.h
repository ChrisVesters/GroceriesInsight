#ifndef INCLUDE_JSONMAPPER_H_
#define INCLUDE_JSONMAPPER_H_

#include <fstream>

#include "DataMapper.h"

using namespace std;

// Currently does not really satisfy the Json spec.
class JsonMapper : public DataMapper {
public:
	JsonMapper(const string fileName);

	const DataGatherer load();

	void save(const DataGatherer data);

private:
	void save(ofstream * file, Node * node, int indent = 0);

	void writeIndent(ofstream* file, int indent);

	void writeOpenObject(ofstream* file, string tagName);

	void writeKey(ofstream * file, string key);

	void writeValue(ofstream* file, string value);

	void writeCloseObject(ofstream* file);

	void writeNewLine(ofstream* file);

	string extractValue(string raw);

	const string fileName;
	stack<string> objects;
};


#endif /* INCLUDE_JSONMAPPER_H_ */
