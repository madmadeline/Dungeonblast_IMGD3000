#pragma once

#include "Object.h"

#define GAME_MAP Map::getInstance()

class Map : public df::Object {

private:
	Map();						// private since singleton
	Map(Map const&);			// don't allow copy
	void operator=(Map const&);	// don't allow assignment

public:
	// get the singleton instance of the Map
	static Map& getInstance();

	~Map();
	
	
	//Map(df::Vector pos);

};

