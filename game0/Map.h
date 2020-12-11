#pragma once

#include "Object.h"
#include "PlayerEvent.h"

#define GAME_MAP Map::getInstance()

class Map : public df::Object {

private:
	//Map();						// private since singleton
	//Map(Map const&);			// don't allow copy
	//void operator=(Map const&);	// don't allow assignment
	df::Vector player_pos;

public:
	// get the singleton instance of the Map
	//static Map& getInstance();
	Map();

	~Map();

	int eventHandler(const df::Event* p_e);

	int draw();

	void setPPos(const PlayerEvent* p_e);

	//Map(df::Vector pos);

};

