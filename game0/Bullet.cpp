#include "EventOut.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "Bullet.h"
#include <DisplayManager.h>

Bullet::Bullet(df::Vector hero_pos) {
	setType("Bullet");

	//soft allows for collisions but doesn't block stuff from moving
	setSolidness(df::SOFT);

	//bullet initial location based on hero
	df::Vector p(hero_pos.getX(), hero_pos.getY());
	setPosition(p);

	registerInterest(df::COLLISION_EVENT);

	//bullets move 1 space each game loop, dir set when hero fires
	setSpeed(1);
}

// DRAW 
int Bullet::draw() {
	return DM.drawCh(getPosition(), 'o', df::YELLOW);
}

void Bullet::collide(const df::EventCollision* p_c) {
	if (((p_c->getObject1()->getType()) == "Goblin") ||
		((p_c->getObject2()->getType()) == "Goblin")) {
		WM.markForDelete(this);
	}

	if (((p_c->getObject1()->getType()) == "Boss") ||
		((p_c->getObject2()->getType()) == "Boss")) {
		WM.markForDelete(this);
	}
}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		out();
		return 1;
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collide(p_collision_event);
		return 1;
	}
	return 0;
}

//COLLISION STUFF
void Bullet::hit(const df::EventCollision* p_collision_event) {

}

//OUT OF BOUNDS
void Bullet::out() {
	WM.markForDelete(this);
}
