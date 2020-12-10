#include "Map.h"
#include "WorldManager.h"
#include "Utility.h"
#include "PlayerEvent.h"
#include "DisplayManager.h"
#include "LogManager.h"

Map::Map() {

	setSprite("MapTest");
	setType("Map");

	setSolidness(df::SPECTRAL);
	setPosition(df::Vector(128,48)); // change

	setAltitude(0);

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
		setPPos(p_player_event);
		return 1;
	}
	else
		return Object::eventHandler(p_e);
}

int Map::draw() {
	int x_abs_max = getAnimation().getSprite()->getWidth();
	int y_abs_max = getAnimation().getSprite()->getHeight();

	float wind_w = (float)x_abs_max * 1.0/3;
	float wind_h = (float)y_abs_max * 1.0/4;

	int x_min = (int)player_pos.getX() - (int)wind_w;
	int x_max = (int)player_pos.getX() + (int)wind_w;
	int y_min = (int)player_pos.getY() - (int)wind_h;
	int y_max = (int)player_pos.getY() + (int)wind_h;

	if (x_min < 0)
		x_min = 0;
	if (x_max >= x_abs_max)
		x_max = x_abs_max - 1;
	if (y_min < 0)
		y_min = 0;
	if (y_max >= y_abs_max)
		y_max = y_abs_max - 1;

	std::string map_str = GAME_MAP.getAnimation().getSprite()->getFrame(0).getString();
	int map_w = GAME_MAP.getAnimation().getSprite()->getFrame(0).getWidth();
	df::Color color = GAME_MAP.getAnimation().getSprite()->getColor();

	for (int i = x_min; i < x_max; i++) {
		for (int j = y_min; j < y_max; j++) {
			char c = map_str[i + (j * map_w)];
			//df::Vector v = df::worldToView(df::Vector(i,j));
			if (DM.drawCh(df::Vector(i, j+1), c, color) == -1)
				LM.writeLog("MAP::DRAW() FAILED TO DRAW CHARACTER AT %d, %d", i, j);
		}
	}
	return 1;
}

void Map::setPPos(const PlayerEvent* p_e) {
	player_pos = p_e->player_pos;
}

/*
Map::Map(df::Vector pos) {
	setSprite("MapTest");
	setType("Map");
	setSolidness(df::HARD);
	setPosition(pos);
}
*/
