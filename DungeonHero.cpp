#include "DungeonHero.h"

#include "EventMouse.h"
#include "EventStep.h"
#include "EventView.h"
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "Bullet.h"
#include "Fireball.h"

//CONSTRUCTOR
DungeonHero::DungeonHero() {
	setType("Hero");

	//register interests
	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
	registerInterest(df::MSE_EVENT);
	registerInterest(df::COLLISION_EVENT);

	//set init position
	df::Vector p(7, WM.getBoundary().getVertical() / 2);
	setPosition(p);

	//set init variables
	fire_slowdown = 15;
	fire_countdown = fire_slowdown;
	move_slowdown = 2;
	move_countdown = move_slowdown;
	hp = 100;
	ammo = 0; //SET LATER
	currentDir = 4; //1 = up
					//2 = down
					//3 = left
					//4 = right
	equipped = 0; //0 = gun
				  //1 = magic
}

//DESTRUCTOR
DungeonHero::~DungeonHero(){

}

//EVENT HANDLER
int DungeonHero::eventHandler(const df::Event* p_e){
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		kbd(p_keyboard_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event =
			dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
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

// DRAW 
int DungeonHero::draw() {
	return DM.drawCh(getPosition(), 'H', df::BLUE);
}

//KEYBOARD STUFF
void DungeonHero::kbd(const df::EventKeyboard* p_keyboard_event){

	switch (p_keyboard_event->getKey()) {
	case df::Keyboard::W:       // up
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 1;
			move(-1);
		break;
	case df::Keyboard::S:       // down
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 2;
			move(1);
		break;
	case df::Keyboard::A:		//left
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 3;
			advance(-1);
		break;
	case df::Keyboard::D:       // right
		if (p_keyboard_event->getKeyboardAction() == df::KEY_DOWN)
			currentDir = 4;
			advance(1);
		break;
	case df::Keyboard::SPACE:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			fire();
			break;
	case df::Keyboard::E:
		if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
			if (equipped == 0) {
				equipped = 1;
			}
			else {
				equipped = 0;
			}
		break;
	default: //other key pressed
		return;
	};

	return;
}

//MOVE THE HERO UP OR DOWN
void DungeonHero::move(int dir){
	// See if time to move.
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX(), getPosition().getY() + dir);
	if ((new_pos.getY() > 3) &&
		(new_pos.getY() < WM.getBoundary().getVertical() - 1))
		WM.moveObject(this, new_pos);
}

//MOVE THE HERO LEFT OR RIGHT
void DungeonHero::advance(int dir) {
	//see if time to move
	if (move_countdown > 0)
		return;
	move_countdown = move_slowdown;

	// If stays on window, allow move.
	df::Vector new_pos(getPosition().getX() + dir, getPosition().getY());
	if ((new_pos.getX() > 3) &&
		(new_pos.getX() < WM.getBoundary().getHorizontal() - 1))
		WM.moveObject(this, new_pos);
}

//FIRE BULLET/MAGIC
void DungeonHero::fire(){
	if (fire_countdown > 0)
		return;
	fire_countdown = fire_slowdown;

	df::Vector v;
	//direction of fire is based on currentDir
	if (currentDir == 1) {
		//up
		v = df::Vector(0, -1);
	}
	else if (currentDir == 2) {
		//down
		v = df::Vector(0, 1);
	}
	else if (currentDir == 3) {
		//left
		v = df::Vector(-1, 0);
	}
	else if (currentDir == 4) {
		//right
		v = df::Vector(1, 0);
	}

	if (equipped == 0) {
		//gun equipped
		Bullet* p = new Bullet(getPosition());
		p->setVelocity(v);
	}
	else if (equipped == 1) {
		//magic equipped
		Fireball* p = new Fireball(getPosition());
		p->setVelocity(v);
	}

}

//MOUSE EVENT
void DungeonHero::mouse(const df::EventMouse* p_mouse_event) {
	//pressed button?
	/*if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
		(p_mouse_event->getMouseButton() == df::Mouse::LEFT))
		fire(p_mouse_event->getMousePosition());*/
}

//STEP EVENT STUFF
void DungeonHero::step(){
	move_countdown--;
	if (move_countdown < 0) {
		move_countdown = 0;
	}
	fire_countdown--;
	if (fire_countdown < 0) {
		fire_countdown = 0;
	}
}

//COLLISION EVENT STUFF
void DungeonHero::collide(const df::EventCollision* p_c){
	//if hero on enemy, decrease hero hp.
	if (((p_c->getObject1()->getType()) == "Goblin") ||
		((p_c->getObject2()->getType()) == "Goblin")) {
		hp -= 20;
		if (hp <= 0) {
			//game over
			WM.markForDelete(this);
		}
		//when hit, hero should go back to starting position.
		df::Vector p(7, WM.getBoundary().getVertical() / 2);
		setPosition(p);
		//shake screen a little
		DM.shake(5, 5, 5);
		//play explosion sound
		df::Sound* p_sound = RM.getSound("explode");
		p_sound->play();
	}
}