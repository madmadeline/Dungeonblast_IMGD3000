#include "Map.h"
#include "WorldManager.h"
#include "Utility.h"

/*Map::Map() {

	setSprite("MapTest");
	setType("Map");
	
	setSolidness(df::SPECTRAL);
	setPosition(df::Vector(44,25));
}

Map& Map::getInstance() {
	static Map map;
	return map;
}*/

Map::Map(df::Vector pos) {
	setSprite("MapTest");
	setType("Map");

	setSolidness(df::HARD);
	setPosition(pos);
}
