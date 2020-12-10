#include "Map.h"
#include "WorldManager.h"
#include "Utility.h"
#include "EventPlayer.h"

Map::Map() {

	setSprite("MapTest");
	setType("Map");

	setSolidness(df::SPECTRAL);
	setPosition(df::Vector(128,48)); // change

	registerInterest(PLAYER_EVENT);
}

Map& Map::getInstance() {
	static Map map;
	return map;
}

Map::~Map() {
}

int Map::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == PLAYER_EVENT) {
		const PlayerEvent* p_player_event =
			dynamic_cast <const PlayerEvent*> (p_e);
		player_pos = p_player_event->getPos();
		return 1;
	}
	return 0;
}

int Map::draw() {
	int x_abs_max = getAnimation().getSprite()->getWidth();
	int y_abs_max = getAnimation().getSprite()->getHeight();

	df::Box window = WM.getBoundary();
	return 0;
}

/*
Map::Map(df::Vector pos) {
	setSprite("MapTest");
	setType("Map");
	setSolidness(df::HARD);
	setPosition(pos);
}
*/
