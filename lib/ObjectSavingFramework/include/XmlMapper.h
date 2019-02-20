#ifndef INCLUDE_XMLMAPPER_H_
#define INCLUDE_XMLMAPPER_H_

#include <fstream>
#include <typeinfo>

#include "DataMapper.h"

using namespace std;

class XmlMapper: public DataMapper {
public:
	XmlMapper(const string fileName);

	const DataGatherer load();

	void save(const DataGatherer data);

private:
	void save(ofstream * file, Node * node, int indent = 0);

	void writeIndent(ofstream* file, int indent);

	void writeOpenTag(ofstream* file, string tagName);

	void writeValue(ofstream* file, string value);

	void writeCloseTag(ofstream* file, string tagName);

	void writeNewLine(ofstream* file);

	const string fileName;
};

#endif /* INCLUDE_XMLMAPPER_H_ */
