#include "Goblin.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "DisplayManager.h"
#include <stdlib.h>
#include "GameUtility.h"
#include <iostream>
#include <EventStep.h>

Goblin::Goblin(int x, int y, int d) {
	setType("Goblin");
	setSprite("Goblin");
	this->getAnimation().getSprite()->setTransparency(' ');

	setPosition(df::Vector(x, y));

	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);
	move_slowdown = 2;
	move_countdown = move_slowdown;
	hp = 12;
	dir = d; //controls the initial direction of the goblin. 
			   //1 = up
			   //-1 = down
			   //2 = left
			   //-2 = right
}

int Goblin::eventHandler(const df::Event* p_e) {

	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return 1;
	}

	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}

	return 0;
}

Goblin::~Goblin() {

}

//STEP EVENT STUFF
void Goblin::step() {
	move_countdown--;
	if (move_countdown < 0) {
		//LM.writeLog("goblin can move");
		move_countdown = 0;
		move(dir);
	}
}

// DRAW 
int Goblin::draw() {
	//return DM.drawCh(getPosition(), 'X', df::GREEN);
	return Object::draw();
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

void Goblin::move(int d) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;
	//set the velocity depending on the direction
	df::Vector new_pos(getPosition().getX(), getPosition().getY());
	LM.writeLog("MOVING A GOBLIN");

	switch (d) {
	case 1:
		new_pos.setY((new_pos.getY()) - 1);

		if (checkOverlapMap(this, new_pos, d) == true) {
			LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}

		//set velocity up
		setVelocity(df::Vector(0, -0.25));
		break;
	case -1:
		new_pos.setY((new_pos.getY()) + 2);

		if (checkOverlapMap(this, new_pos, d) == true) {
			LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}
		//set velocity down
		setVelocity(df::Vector(0, 0.25));
		break;
	case 2:
		new_pos.setX((new_pos.getX()) - 2);

		if (checkOverlapMap(this, new_pos, d) == true) {
			LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}
		//set velocity left
		setVelocity(df::Vector(-0.5, 0));
		break;
	case -2:
		new_pos.setX((new_pos.getX()) + 2);

		if (checkOverlapMap(this, new_pos, d) == true) {
			LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}
		//set velocity right
		setVelocity(df::Vector(0.5, 0));
		break;
	}
}

