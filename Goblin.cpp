#include "Goblin.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "DisplayManager.h"
#include <stdlib.h>

Goblin::Goblin() {
	setType("Goblin");
	//setVelocity(df::Vector(-0.25, 0));

	//set init position
	df::Vector p(70, WM.getBoundary().getVertical() / 2);
	setPosition(p);

	registerInterest(df::COLLISION_EVENT);
	hp = 12;
}

int Goblin::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	return 0;
}

Goblin::~Goblin() {

}

// DRAW 
int Goblin::draw() {
	return DM.drawCh(getPosition(), 'X', df::GREEN);
}


void Goblin::hit(const df::EventCollision* p_c) {
	//if enemy on enemy collision, ignore
	if ((p_c->getObject1()->getType() == "Goblin") &&
		(p_c->getObject2()->getType() == "Goblin"))
		return;
	//if bullet on enemy
	if ((p_c->getObject1()->getType() == "Bullet") ||
		(p_c->getObject2()->getType() == "Bullet")) {
		//decrease enemy hp and check to see if zero
		hp -= 6;
		if (hp <= 0) {
			WM.markForDelete(this);
		}
	}
	//if fireball on enemy
	if ((p_c->getObject1()->getType() == "Fireball") ||
		(p_c->getObject2()->getType() == "Fireball")) {
		//decrease enemy hp and check to see if zero
		hp -= 4;
		if (hp >= 0) {
			WM.markForDelete(this);
		}
	}
	//if hero on enemy
	if (((p_c->getObject1()->getType()) == "Hero") ||
		((p_c->getObject2()->getType()) == "Hero")) {
		WM.markForDelete(this); //delete the enemy
	}
}