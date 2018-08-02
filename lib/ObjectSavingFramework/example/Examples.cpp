#include "../src/ConsoleMapper.cpp"
#include "../src/XmlMapper.cpp"
#include "../src/JsonMapper.cpp"
#include "../src/Node.h"
#include "../src/DataGatherer.h"

#include <iostream>

int main(int argc, char* argv[]) {
	DataGatherer gatherer;
	
	// This completely hides the structure!
	gatherer.startObject("object");
	gatherer.addValue("foo", "hello");
	gatherer.addValue("bar", "world");
	gatherer.addValue("int", "5");
	gatherer.endObject("object");
	
	JsonMapper json("output/data.json");
	json.save(gatherer);
	gatherer = json.load();
	
	ConsoleMapper console;
	console.save(gatherer);
	
	// Just loads the object!
	gatherer.loadObject("object");
	cout << gatherer.getValue("foo") << endl;
	cout << gatherer.getValue("bar") << endl;
	gatherer.releaseObject("object");
}