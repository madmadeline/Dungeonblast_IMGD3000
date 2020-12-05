#include "EventOut.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Fireball.h"
#include <DisplayManager.h>

Fireball::Fireball(df::Vector hero_pos) {
	setType("Fireball");

	//soft allows for collisions but doesn't block stuff from moving
	setSolidness(df::SOFT);

	//bullet initial location based on hero
	df::Vector p(hero_pos.getX() + 3, hero_pos.getY());
	setPosition(p);

	//bullets move 1 space each game loop, dir set when hero fires
	setSpeed(1);
}

// DRAW 
int Fireball::draw() {
	return DM.drawCh(getPosition(), 'o', df::RED);
}

int Fireball::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	return 0;
}

//COLLISION STUFF
void Fireball::hit(const df::EventCollision* p_collision_event) {

}

//OUT OF BOUNDS
void Fireball::out() {
	WM.markForDelete(this);
}
