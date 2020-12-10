#pragma once

#include "Object.h"

#define GAME_MAP Map::getInstance()

class Map : public df::Object {

private:
	Map();						// private since singleton
	Map(Map const&);			// don't allow copy
	void operator=(Map const&);	// don't allow assignment
	df::Vector player_pos;

public:
	// get the singleton instance of the Map
	static Map& getInstance();

	~Map();

	int eventHandler(const df::Event* p_e);

	int draw();

	//Map(df::Vector pos);

};

