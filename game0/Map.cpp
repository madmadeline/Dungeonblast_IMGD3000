#include "Map.h"
#include "WorldManager.h"
#include "Utility.h"

Map::Map() {

	setSprite("MapTest");
	setType("Map");

	setSolidness(df::SPECTRAL);
	setPosition(df::Vector(30,15)); // change
}

Map& Map::getInstance() {
	static Map map;
	return map;
}

Map::~Map() {
}

/*
Map::Map(df::Vector pos) {
	setSprite("MapTest");
	setType("Map");
	setSolidness(df::HARD);
	setPosition(pos);
}
*/
