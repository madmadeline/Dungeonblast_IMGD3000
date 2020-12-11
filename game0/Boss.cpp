#include "Boss.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "DisplayManager.h"
#include <stdlib.h>
#include "GameUtility.h"
#include <iostream>
#include <EventStep.h>
#include "PlayerEvent.h"
#include "Fireball.h"

Boss::Boss(int x, int y) {
	setType("Boss");
	setSprite("Dragon");

	setPosition(df::Vector(x, y));

	registerInterest(df::COLLISION_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(PLAYER_EVENT);
	move_slowdown = 2;
	move_countdown = move_slowdown;
	fire_slowdown = 60;
	fire_countdown = fire_slowdown;
	hp = 50;
	dir = 1; //controls the initial direction of the boss. 
			   //1 = up
			   //-1 = down
			   //2 = left
			   //-2 = right
	target = df::Vector(0, 0);
}

int Boss::eventHandler(const df::Event* p_e) {

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

	if (p_e->getType() == PLAYER_EVENT) {
		//update the target
		const PlayerEvent* p_player_event =
			dynamic_cast <const PlayerEvent*> (p_e);
		target = p_player_event->getPos();
	}

	return 0;
}

Boss::~Boss() {

}

//STEP EVENT STUFF
void Boss::step() {
	move_countdown--;
	if (move_countdown < 0) {
		//LM.writeLog("goblin can move");
		move_countdown = 0;
		move(dir);
	}
	//if the hero is in range, start firing.
	fire_countdown--;
	if ((getPosition().getX() - target.getX()) <= 10 &&
		(target.getX() - getPosition().getX()) >= 0 &&
		(getPosition().getY() - target.getY()) <= 10) {
		fire();
	}

}

//FIRE
void Boss::fire() {
	//create a fireball and send it at the player
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	df::Vector v = target - getPosition();
	v.normalize();
	v.scale(1);
	//magic equipped
	df::Sound* p_sound = RM.getSound("Fireball");
	p_sound->play();
	df::Vector fire_pos = getPosition();
	fire_pos.setX(getPosition().getX() + 5);
	Fireball* p = new Fireball(fire_pos);
	p->setVelocity(v);
}

// DRAW 
int Boss::draw() {
	//return DM.drawCh(getPosition(), 'X', df::GREEN);
	return Object::draw();
}

void Boss::hit(const df::EventCollision* p_c) {
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

void Boss::move(int d) {
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;
	//set the velocity depending on the direction
	df::Vector new_pos(getPosition().getX(), getPosition().getY());
	//LM.writeLog("MOVING A GOBLIN");

	switch (d) {
	case 1:
		new_pos.setY((new_pos.getY()) - 1);

		if (checkOverlapMap(this, new_pos, d) == true) {
			//LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}

		//set velocity up
		setVelocity(df::Vector(0, -0.25));
		break;
	case -1:
		new_pos.setY((new_pos.getY()) + 2);

		if (checkOverlapMap(this, new_pos, d) == true) {
			//LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}
		//set velocity down
		setVelocity(df::Vector(0, 0.25));
		break;
	case 2:
		new_pos.setX((new_pos.getX()) - 2);

		if (checkOverlapMap(this, new_pos, d) == true) {
			//LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}
		//set velocity left
		setVelocity(df::Vector(-0.5, 0));
		break;
	case -2:
		new_pos.setX((new_pos.getX()) + 2);

		if (checkOverlapMap(this, new_pos, d) == true) {
			//LM.writeLog("GOBLIN OVERLAPPED MAP!!");
			dir = -dir;
			return;	// overlaps, switch direction, else continue
		}
		//set velocity right
		setVelocity(df::Vector(0.5, 0));
		break;
	}
}

