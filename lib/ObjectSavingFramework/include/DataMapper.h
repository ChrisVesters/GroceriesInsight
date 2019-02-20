#ifndef  DATAMAPPER_H
#define DATAMAPPER_H

#include "DataGatherer.h"
#include "Node.h"

class DataMapper {
public:
	virtual const DataGatherer load() = 0;
	virtual void save(const DataGatherer data) = 0;
	virtual ~DataMapper() {};
};

#endif
