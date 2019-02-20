#ifndef INCLUDE_CONSOLEMAPPER_H_
#define INCLUDE_CONSOLEMAPPER_H_

#include <iostream>

#include "DataMapper.h"

using namespace std;

class ConsoleMapper : public DataMapper {
public:
	const DataGatherer load();

	void save(const DataGatherer data);

private:
	void print(const Node * node, int indent = 0);
};




#endif /* INCLUDE_CONSOLEMAPPER_H_ */
